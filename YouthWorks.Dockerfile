FROM centos:7

RUN yum update -y && \
    yum -y install libcsv-devel.x86_64 zlib-devel.x86_64 automake && \
    yum clean all

RUN git clone https://github.com/jmcnamara/libxlsxwriter.git && \
    cd libxlsxwriter && \
    make && \
    sudo make install

RUN useradd -m youthworks
RUN install -d -o youthworks -g youthworks /workdir
USER youthworks
WORKDIR /workdir

RUN git clone git@github.com:weaversa/BaltimoreYouthWorks.git . && git submodule update --init --remote

RUN tar -xvzf GTL-1.2.4-lgpl.tar.gz && \
    cd GTL-1.2.4 && \
    ./configure && \
    make &&
    make install

RUN git clone git@github.com:rdmpage/maximum-weighted-bipartite-matching.git && \
    cd maximum-weighted-bipartite-matching && \
    aclocal && \
    autoconf && \
    automake && \
    ./configure && \
    make && \
    make install

RUN cd YouthWorks && \
    make && \
    make test/test

CMD ["/bin/bash"]
