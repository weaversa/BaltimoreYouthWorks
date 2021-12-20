FROM centos:7

RUN yum -y update
RUN yum -y install git make automake gcc gcc-c++ libcsv-devel.x86_64 zlib-devel.x86_64

RUN git clone https://github.com/rdmpage/graph-template-library.git && \
    cd graph-template-library && \
    ./configure && \
    make && \
    make install

RUN git clone https://github.com/rdmpage/maximum-weighted-bipartite-matching.git && \
    cd maximum-weighted-bipartite-matching && \
    aclocal && \
    autoconf && \
    automake --add-missing && \
    ./configure && \
    make && \
    make install

RUN git clone https://github.com/jmcnamara/libxlsxwriter.git && \
    cd libxlsxwriter && \
    make && \
    make install

RUN git clone https://github.com/weaversa/BaltimoreYouthWorks.git && \
    cd YouthWorks && \
    make && \
    make test/test

CMD ["/bin/bash"]
