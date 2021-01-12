//GH_UP_MISC_1

#include <arrow/api.h>
#include <memory>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include <parquet/exception.h>
#include <iostream>
#include <string>
#include <arrow/type_fwd.h>

using namespace std;

int main()
{
    std::shared_ptr<arrow::io::ReadableFile> infile;
    //V6P
    //string source = "vinoth.parquet";

    PARQUET_ASSIGN_OR_THROW(infile, arrow::io::ReadableFile::Open(source,
                                                                  arrow::default_memory_pool()));
    parquet::arrow::FileReaderBuilder builder;
    parquet::ReaderProperties properties = parquet::default_reader_properties();
    parquet::ArrowReaderProperties arrowprops(true);
    arrowprops.set_batch_size(10000);
    arrowprops.set_pre_buffer(true);
    PARQUET_THROW_NOT_OK(builder.Open(infile, properties));
    std::unique_ptr<parquet::arrow::FileReader> pFileReader;
    PARQUET_THROW_NOT_OK(builder.properties(arrowprops)->Build(&pFileReader));

    std::shared_ptr<parquet::FileMetaData> pFileMetaData;
    pFileMetaData = pFileReader->parquet_reader()->metadata();

    //std::cout << " \nNumber of rows " << pFileMetaData->RowGroup(0)->num_rows() << std::endl;

    std::shared_ptr<arrow::Schema> arrowSchemaPtr;
    pFileReader->GetSchema(&arrowSchemaPtr);

    for (int32_t dwRowGroupIdx = 0; dwRowGroupIdx < pFileMetaData->num_row_groups(); dwRowGroupIdx++)
    {
        vector<std::shared_ptr<::arrow::Array>> arrowArrayVec(arrowSchemaPtr->num_fields());
        std::shared_ptr<parquet::arrow::RowGroupReader> rgReader = pFileReader->RowGroup(dwRowGroupIdx);
        uint32_t dwNumberOfRows = -1;

        std::shared_ptr<parquet::arrow::ColumnChunkReader> colReaderVec;
        for (int32_t dwColIdx = 0; dwColIdx < arrowSchemaPtr->num_fields(); dwColIdx++)
        {
            colReaderVec = rgReader->Column(dwColIdx);

            std::shared_ptr<arrow::ChunkedArray> ChunkedArray;
            colReaderVec->Read(&ChunkedArray);
            dwNumberOfRows = ChunkedArray->length(); //V6P Move independent of chunk array

            arrowArrayVec[dwColIdx] = std::move(ChunkedArray->chunk(0)); //V6P-Handle multiple chunks.
        }

        for (int32_t dwRowIdx = 0; dwRowIdx < dwNumberOfRows; dwRowIdx++)
        {
            for (int32_t dwColIdx = 0; dwColIdx < arrowSchemaPtr->num_fields(); dwColIdx++)
            {
                const arrow::Type::type &colType = arrowSchemaPtr->field(dwColIdx)->type()->id();

                switch (colType)
                {
                //V6P Change mutable values to getValues
                case arrow::Type::INT64:
                    //std::cout   << (arrowArrayVec[dwColIdx]->data()->GetMutableValues<int64_t>(1)[i]) <<",";
                    std::cout << (arrowArrayVec[dwColIdx]->data()->GetValues<int64_t>(1)[dwRowIdx]) << ",";
                    break;

                case arrow::Type::DOUBLE:
                    std::cout << (arrowArrayVec[dwColIdx]->data()->GetValues<double>(1)[dwRowIdx]) << ",";
                    break;

                case arrow::Type::STRING:
                    //1st Pos - Size of string
                    //2nd in array - Value of string

                    //V6P - optimize reading part

                    uint8_t *valuePtr = arrowArrayVec[dwColIdx]->data()->GetMutableValues<uint8_t>(2) + arrowArrayVec[dwColIdx]->data()->GetValues<int32_t>(1)[dwRowIdx];
                    std::cout << string((const char *)valuePtr, arrowArrayVec[dwColIdx]->data()->GetValues<int32_t>(1)[dwRowIdx + 1] - arrowArrayVec[dwColIdx]->data()->GetValues<int32_t>(1)[dwRowIdx]) << ",";
                    break;
                }
            }

            std::cout << '\n';
        }
    }
}
