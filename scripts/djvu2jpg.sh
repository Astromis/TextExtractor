#!/bin/sh
# djvu -> jpgs converter

i=1

# number of pages (392)
while [ $i -ne 10 ]
do
ddjvu -page=$i -format=pnm ../examples/test_without_text.djvu $i.pnm
pnmtojpeg $i.pnm > $i.jpg
rm -f $i.pnm
echo "page $i done"
i=`expr $i + 1`
done
