#!/usr/bin/env bash
DIR_WWW=/var/www/reiscout.com
DIR_PRIVATE_FILES=${DIR_WWW}/private_files
DIR_PUBLIC_FILES=${DIR_WWW}/docroot/sites/default/files
DIR_BACKUPS=${DIR_WWW}/backups

#Backup private files
cd ${DIR_PRIVATE_FILES}
FILEPATH_PRIVATE_FILES_BACKUP=${DIR_BACKUPS}/private-files-`date +%F-%T`.tgz
tar -czf ${FILEPATH_PRIVATE_FILES_BACKUP} .
aws s3 cp ${FILEPATH_PRIVATE_FILES_BACKUP} s3://reiscout/site-backups/
rm ${FILEPATH_PRIVATE_FILES_BACKUP}

#Backup public files
cd ${DIR_PUBLIC_FILES}
FILEPATH_PUBLIC_FILES_BACKUP=${DIR_BACKUPS}/public-files-`date +%F-%T`.tgz
tar -czf ${FILEPATH_PUBLIC_FILES_BACKUP} .
aws s3 cp ${FILEPATH_PUBLIC_FILES_BACKUP} s3://reiscout/site-backups/
rm ${FILEPATH_PUBLIC_FILES_BACKUP}

#Backup database
FILEPATH_DB_BACKUP=${DIR_BACKUPS}/db-`date +%F-%T`.sql
drush sql-dump --gzip --result-file=${FILEPATH_DB_BACKUP}
aws s3 cp ${FILEPATH_DB_BACKUP}.gz s3://reiscout/site-backups/
rm ${FILEPATH_DB_BACKUP}.gz
