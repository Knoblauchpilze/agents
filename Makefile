debug:
	mkdir -p build/Debug && cd build/Debug && cmake -DCMAKE_BUILD_TYPE=Debug ../.. && make -j 8

release:
	mkdir -p build/Release && cd build/Release && cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j 8

clean:
	rm -rf build

cleanSandbox:
	rm -rf sandbox

copyRelease:
	rsync -avH build/Release/lib build/Release/bin sandbox/

copyDebug:
	rsync -avH build/Debug/lib build/Debug/bin sandbox/

copy:
	mkdir -p sandbox/
	rsync -avH data sandbox/
	mkdir -p sandbox/data/saves
	mv sandbox/data/*.sh sandbox/

sandbox: release copy copyRelease

sandboxDebug: debug copy copyDebug

run: sandbox
	cd sandbox && ./run.sh local

drun: sandboxDebug
	cd sandbox && ./debug.sh local

v: sandboxDebug
	cd sandbox && ./valgrind.sh local

profile: sandboxDebug
	cd sandbox && ./profile.sh local
