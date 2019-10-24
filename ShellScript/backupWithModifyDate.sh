source=/vinoth/sourceCode
dest=/vinoth/v6Backup

folderbasename=V6BackupLinux

destFolderName="$folderbasename"_$(date +%Y_%m_%d_%H_%M_%S)

cd $dest
mkdir -p $destFolderName
cd -

find $source -type f -mtime -1 ! -name '*.o' ! -name '*core*' ! -name '*.log' ! -path '/*/.git/*' -exec cp -a "{}" $dest/$destFolderName \;



cd $dest

tar -zcvf "$destFolderName".tar.gz $destFolderName 
#rm -rf $destFolderName
cd -
