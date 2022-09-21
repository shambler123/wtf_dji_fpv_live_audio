NAME = $(shell cat ./control/control | grep Package | cut -d" " -f2)
ARCH = $(shell cat ./control/control | grep Architecture | cut -d" " -f2)
VERSION = $(shell cat ./control/control | grep Version | cut -d" " -f2)
IPK_NAME = "${NAME}_${VERSION}_${ARCH}.ipk"

all:
	mkdir -p tmp
	echo "2.0" > tmp/debian-binary
	cp -r data tmp/
	cp -r control tmp/
	chmod +x tmp/control/postinst
	chmod +x tmp/control/prerm
	cd tmp/control && tar -czvf ../control.tar.gz .
	cd tmp/data && tar -czvf ../data.tar.gz .
	cd tmp/ && tar -czvf "../${IPK_NAME}" ./control.tar.gz ./data.tar.gz ./debian-binary

clean:
	rm -rf tmp