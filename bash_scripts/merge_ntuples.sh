#!/bin/bash

usage () {
  echo
  echo "Usage: source merge_ntuples.sh <input_directory> <output_file>"
  echo
}

if [ -z "${1}" ] || [ -z "${2}" ]
then
  usage
  return 1
fi

if [ "${1:-1:}" != "/" ]
then
  in_dir="${1}/"
else
  in_dir=${1}
fi

if [ -e ${2} ]
then

  echo
  echo "To merge the files, the output file should not exists"

  while [ true ]
  do
    echo -n "Delete ${2}? ([Y]/n)"
    read confirm

    if [ "${confirm}" == "n" ] || [ "${confirm}" == "N" ]
    then
      echo
      echo "${2} not deleted"
      echo
      break

    elif [ "${confirm}" == "y" ] || [ "${confirm}" == "Y" ] || [ "${confirm}" == "" ]
    then
      rm ${2}
      echo
      echo "${2} deleted"
      echo
      break

    fi

  done

fi

rootfiles="$(ls ${in_dir}*.root)"
rootfiles="$(echo ${rootfiles})"
hadd ${2} ${rootfiles}
