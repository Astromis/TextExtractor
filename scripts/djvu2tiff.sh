#!/bin/sh
# djvu -> jpgs converter

i=1

# number of pages (392)
while [ $i -ne 392 ]
do
ddjvu -page=$i -format=tiff ../examples/test_without_text.djvu $i.tiff
#pnmtojpeg $i.pnm > $i.jpg
#rm -f $i.pnm
echo "page $i done"
i=`expr $i + 1`
done
