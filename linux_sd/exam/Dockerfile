ARG PACKAGE=
ARG ARCH=

FROM rosalab/rosa13 AS builder
ARG PACKAGE
ARG ARCH

ARG FULL_PACKAGE=texlive-${PACKAGE}

RUN dnf up -y && dnf install -y rpm-build rpmdevtools && rpmdev-setuptree

COPY ${FULL_PACKAGE}/*.tar.xz /root/rpmbuild/SOURCES
COPY ${FULL_PACKAGE}/${FULL_PACKAGE}.spec /root/rpmbuild/SPECS/${FULL_PACKAGE}.spec 

RUN dnf install -y $(rpmspec -q --buildrequires /root/rpmbuild/SPECS/${FULL_PACKAGE}.spec)
RUN rpmbuild -bb /root/rpmbuild/SPECS/${FULL_PACKAGE}.spec --target ${ARCH}

FROM rosalab/rosa13
ARG ARCH

COPY --from=builder /root/rpmbuild/RPMS/${ARCH} /output
CMD [ "rpm", "-qip", "/output/*.rpm" ]
