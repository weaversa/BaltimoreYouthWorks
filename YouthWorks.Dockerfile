FROM centos:7

RUN yum -y update
RUN yum -y install git make automake gcc gcc-c++ zlib-devel.x86_64 patch

RUN git clone https://github.com/weaversa/BaltimoreYouthWorks.git

RUN git clone https://github.com/rdmpage/graph-template-library.git && \
    cd graph-template-library && \
    ./configure && \
    make && \
    make install

RUN git clone https://github.com/weaversa/maximum-weighted-bipartite-matching.git && \
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

RUN git clone https://github.com/rgamble/libcsv.git && \
    cd libcsv && \
    aclocal && \
    autoconf && \
    automake --add-missing && \
    ./configure && \
    make && \
    make install

RUN cd BaltimoreYouthWorks && \
    make && \
    make test/test && \
    cp test/test /usr/local/bin/youthworks

ENV LD_LIBRARY_PATH=/usr/local/lib

ENTRYPOINT ["/usr/local/bin/youthworks"]
