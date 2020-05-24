all:bigVD fileTooBig fragm smallVD normalAdd addTo copyFrom addSame

bigVD: bigVD.c copy.c crea-del.c deleteFile.c map.c view.c fs.h
	cc -o bigVD bigVD.c copy.c crea-del.c deleteFile.c map.c view.c

fileTooBig: fileTooBig.c copy.c crea-del.c deleteFile.c map.c view.c fs.h
	cc -o fileTooBig fileTooBig.c copy.c crea-del.c deleteFile.c map.c view.c

fragm: fragm.c copy.c crea-del.c deleteFile.c map.c view.c fs.h
	cc -o fragm fragm.c copy.c crea-del.c deleteFile.c map.c view.c

smallVD: smallVD.c copy.c crea-del.c deleteFile.c map.c view.c fs.h
	cc -o smallVD smallVD.c copy.c crea-del.c deleteFile.c map.c view.c

normalAdd: normalAdd.c copy.c crea-del.c deleteFile.c map.c view.c fs.h
	cc -o normalAdd normalAdd.c copy.c crea-del.c deleteFile.c map.c view.c

addTo: addTo.c copy.c crea-del.c deleteFile.c map.c view.c fs.h
	cc -o addTo addTo.c copy.c crea-del.c deleteFile.c map.c view.c

copyFrom: copyFrom.c copy.c crea-del.c deleteFile.c map.c view.c fs.h
	cc -o copyFrom copyFrom.c copy.c crea-del.c deleteFile.c map.c view.c

addSame: addSame.c copy.c crea-del.c deleteFile.c map.c view.c fs.h
	cc -o addSame addSame.c copy.c crea-del.c deleteFile.c map.c view.c

checkCopying:
	./addTo 
	rm plik1.txt
	./copyFrom  

clear:
	rm bigVD fileTooBig fragm smallVD normalAdd addTo copyFrom addSame

