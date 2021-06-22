#!/bin/bash

usage () {
  echo
  echo " Usage: source merge_ntuples.sh -f file [file ...] -o [output]"
  echo
  echo "  Options:"
  echo "    -h, --help           Print the usage."
  echo
}

if [ -z "${1}" ]
then
  usage
  exit 1
fi

while test $# -gt 0
do
  case "${1}" in
    -h|--help)
    usage
    exit 0
    ;;

    -f)
    shift

    if [ -z "${1}" ]
    then
      usage
      exit 2
    fi

    valu=`echo ${1} | grep -c '^-'`

    while [ "${valu}" == "0" ] && [ -n "${1}" ];
    do

      rootfiles="${rootfiles} ${1}"

      shift
      valu=`echo ${1} | grep -c '^-'`

    done
    ;;

    -o)
    shift

    if [ -z "${1}" ]
    then
      usage
      exit 2
    fi

    output="${1}"
    shift
    ;;

    *)
    usage
    exit 3
    ;;

  esac
done

if [ -z "${rootfiles}" ] || [ -z "${output}" ]
then
  usage
  exit 2
fi

if [ -e ${output} ]
then
  echo
  echo "To merge the files, the output file should not exists"

  while [ true ]
  do
    echo -n "Delete ${output}? ([Y]/n)"
    read confirm
    if [ "${confirm}" == "n" ] || [ "${confirm}" == "N" ]
    then
      echo
      echo "${output} not deleted"
      echo
      exit 4

    elif [ "${confirm}" == "y" ] || [ "${confirm}" == "Y" ] || [ "${confirm}" == "" ]
    then
      rm ${output}
      echo
      echo "${output} deleted"
      echo
      break

    fi

  done

fi

hadd ${output} ${rootfiles}
