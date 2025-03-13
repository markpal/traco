The TRACO Compiler  2015-2025

Website: traco.sourceforge.net

Runs on Ubuntu 2024.04, adapted for Python 3 and islpy 2025.1.

See the file:   install_ubuntu_2024_04

Demonstration:
https://traco.sourceforge.net/nussinov.html



Quick Install

sudo apt install flex bison libboost-regex-dev libgmp-dev libntl-dev  graphviz graphviz-dev

sudo pip install –break-system-packages islpy, tqdm, paramiko, graphviz, pygraphviz, python-graph-core, python-graph-dot, easyprocess, termcolor, matplotlib

make all

tar xvzf barvinok-0.41.tar.gz & cd barvinok-0.41 & ./configure & make & sudo make install & cd ..

nano barv_script //correct path

tar xvzf clan-0.8.0.tar.gz & cd clan-0.8.0 & ./configure & make & sudo make install //optional & cd ..

git clone https://github.com/tobiasgrosser/islplot

cd islplot & sudo python3 setup.py install

Good Luck!

