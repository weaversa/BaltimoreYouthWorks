FROM centos:7

RUN yum update -y && \
    yum -y install libcsv-devel.x86_64 zlib-devel.x86_64 && \
    yum clean all

RUN git clone https://github.com/jmcnamara/libxlsxwriter.git && \
    cd libxlsxwriter && \
    make && \
    sudo make install

RUN useradd -m user
USER user

RUN useradd -m youthworks
RUN install -d -o youthworks -g youthworks /workdir
USER youthworks
WORKDIR /workdir

RUN git clone git@github.com:weaversa/BaltimoreYouthWorks.git . && git submodule update --init --remote
RUN make

CMD ["/bin/bash"]
