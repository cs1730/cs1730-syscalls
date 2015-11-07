
for i in `ls /usr/share/man/man7 | sed -e 's/.7.gz//'`; do 
    man -t 7 $i | ps2pdf - $i.7.pdf
done