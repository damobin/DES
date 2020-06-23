#bin/bash
make clean
make
if [ $? -ne 0 ]
	then
		echo "make error"
	else
		echo "sucess!"
		du -h ./bin/*
		./bin/*
fi
