
for i in `ls /usr/share/man/man5 | sed -e 's/.5.gz//'`; do 
    man -t 5 $i | ps2pdf - $i.5.pdf
done