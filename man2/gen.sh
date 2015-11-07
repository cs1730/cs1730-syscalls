
for i in `ls /usr/share/man/man2 | sed -e 's/.2.gz//'`; do 
    man -t 2 $i | ps2pdf - $i.2.pdf
done