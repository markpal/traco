FROM ubuntu:24.04

LABEL maintainer="mpalkowski@zut.edu.pl"
ENV DEBIAN_FRONTEND=noninteractive

# Instalacja narzędzi developerskich, Pythona i dodatkowych bibliotek
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
      ca-certificates \
      wget curl git nano build-essential cmake pkg-config \
      python3 python3-pip python3-venv python3-dev \
      gcc g++ make gdb \
      locales \
      flex bison \
      libboost-regex-dev \
      libgmp-dev libntl-dev \
      graphviz graphviz-dev \
      clang llvm lldb \
      mc nano \
    && rm -rf /var/lib/apt/lists/*

# Ustawienie locale
RUN locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# Dodaj użytkownika dev
ARG USER=dev
ARG UID=1010
ARG GID=1010

RUN groupadd -g ${GID} ${USER} || true && \
    useradd -m -u ${UID} -g ${GID} -s /bin/bash ${USER} || true && \
    mkdir -p /workspace && chown ${USER}:${USER} /workspace
    
# Stworzenie venv
RUN python3 -m venv /opt/venv

# Ustawienie PATH, żeby pip w venv był domyślny
ENV PATH="/opt/venv/bin:$PATH"

# Instalacja pakietów w venv
RUN pip install --upgrade pip setuptools wheel && \
    pip install \
        islpy \
        tqdm \
        paramiko \
        graphviz \
        pygraphviz \
        python-graph-core \
        python-graph-dot \
        easyprocess \
        termcolor \
        pexpect \
        matplotlib && \
    pip cache purge
    

# Przełączamy się tymczasowo na root, żeby sklonować repo
USER root


# Pobranie repozytorium do /workspace/traco
RUN mkdir -p /workspace && \
    git clone --depth 1 https://github.com/markpal/traco.git /workspace/traco && \
    chown -R dev:dev /workspace



# Przejście do katalogu traco
WORKDIR /workspace/traco

# Rozpakowanie i build barvinok
RUN tar -xzf barvinok-0.41.tar.gz && \
    cd barvinok-0.41 && \
    ./configure && \
    make && \
    make install
    
# Rozpakowanie i build clan
WORKDIR /workspace/traco
RUN tar -xzf clan-0.8.0.tar.gz && \
    cd clan-0.8.0 && \
    ./configure && \
    make && \
    make install
    
# Pobranie islplot i instalacja w venv
WORKDIR /workspace
RUN git clone https://github.com/tobiasgrosser/islplot && \
    cd islplot && \
    python3 setup.py install
    
WORKDIR /workspace/traco
RUN make all && make framework

# Tworzenie skryptu barv_script
RUN rm -f barv_script && \
    echo "$PWD/barvinok-0.41/iscc < barvinok_input > ppp" >> barv_script && \
    echo "touch lock" >> barv_script && \
    chmod +x barv_script
    
# Instalacja zamrożonego setuptools
RUN /opt/venv/bin/pip install "setuptools<81"
ENV PYTHONWARNINGS="ignore"

# Ustawiamy właściciela katalogu workspace na dev
RUN chown -R dev:dev /workspace
    
# Przełączamy się z powrotem na dev
USER dev
RUN echo 'export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"' >> ~/.bashrc

WORKDIR /workspace

USER ${USER}
CMD ["/bin/bash"]
