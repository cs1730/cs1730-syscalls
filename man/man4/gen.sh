
for i in `ls /usr/share/man/man4 | sed -e 's/.4.gz//'`; do 
    man -t 4 $i | ps2pdf - $i.4.pdf
done