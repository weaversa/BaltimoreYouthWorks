#!/bin/bash
YOUTH=$(zenity --filename=$HOME/ --file-selection --title="Choose a CSV file containing Youth data" --file-filter='CSV files (csv) | *.csv')
JOBS=$(zenity --filename=$HOME/ --file-selection --title="Choose a CSV file containing Job data" --file-filter='CSV files (csv) | *.csv')
echo ${YOUTH}
echo ${JOBS}

if $(zenity --question --text="Start matching? (This could take a few minutes)") ; then
  /home/moed/local/packages/Youthworks/test/test "${YOUTH}" "${JOBS}" >& ~/Desktop/YouthWorksMatchingStats.txt
  zenity --info --text="Matching complete. Matching XLSX file and Ouput Statistics saved to Desktop."
fi
