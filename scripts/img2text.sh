#!/bin/sh
# djvu -> jpgs converter

i=1

# number of pages (392)
while [ $i -ne 10 ]
do
tesseract $i.pnm $i.txt -l rus
echo "page $i done"
i=`expr $i + 1`
done
