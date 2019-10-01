source=playground/
dest=playground/dest #dont add / at end
folderbasename=V6BackupLinux

destFolderName="$folderbasename"_$(date +%Y_%m_%d_%H_%M_%S)

cd $dest
mkdir -p $destFolderName
cd -

rsync -av --progress $source $dest/$destFolderName  --exclude folder1
cd $dest

tar -zcvf "$destFolderName".tar.gz $destFolderName
rm -rf $destFolderName
cd -
