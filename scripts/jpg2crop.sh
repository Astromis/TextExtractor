#!/bin/sh
# djvu -> jpgs converter

i=1

# number of pages (392)
while [ $i -ne 61 ]
do
python process_text.py $i.jpg
echo "page $i done"
i=`expr $i + 1`
done
