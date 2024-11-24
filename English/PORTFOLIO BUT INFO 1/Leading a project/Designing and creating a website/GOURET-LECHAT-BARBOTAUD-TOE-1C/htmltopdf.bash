#!/bin/bash

docker volume create sae103

docker run -d --name sae103-forever -v sae103:/sae103 clock tail -f /dev/null

sleep 5

docker cp gendoc-tech.php sae103-forever:/sae103/
docker cp gendoc-user.php sae103-forever:/sae103/

docker exec sae103-forever php /sae103/gendoc-tech.php /sae103/doc-tech.html
docker exec sae103-forever php /sae103/gendoc-user.php /sae103/doc-user.html

HTML2PDF_PATH=$(docker exec sae103-forever which html2pdf)

docker exec sae103-forever $HTML2PDF_PATH /sae103/doc-tech.html /sae103/doc-tech.pdf
docker exec sae103-forever $HTML2PDF_PATH /sae103/doc-user.html /sae103/doc-user.pdf

docker exec sae103-forever zip -r /sae103/archive.zip /sae103/*.pdf

docker cp sae103-forever:/sae103/archive.zip archive.zip

docker stop sae103-forever

docker volume rm sae103