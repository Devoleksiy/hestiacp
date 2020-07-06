#!/bin/sh

hestia_module_vsftpd_remove() {
    source $HESTIA/bin/module/func.inc

    ftp_installed=$(hestia_module_isinstalled ftp)
    if [ ! "$ftp_installed" ]; then
        echo "FTP module is not installed. See 'hestia module info ftp'."
        exit 1
    fi

    ftp_variant=$(hestia_module_getvariant ftp)
    if [ "$ftp_variant" != 'vsftpd' ]; then
        echo "The installed FTP module is not vsftpd. See 'hestia module info ftp'."
        exit 1
    fi

    echo "Removing FTP (vsftpd) module..."

    osal_service_stop vsftpd
    osal_service_disable vsftpd
    osal_package_remove vsftpd

    rm -f $OSAL_PATH_VSFTPD_CONF/vsftpd.conf

    osal_ini_set $HESTIA/conf/hestia.conf '' 'FTP_SYSTEM' 'no'
    osal_ini_set $HESTIA/conf/modules.conf 'ftp' 'installed' '0'
    osal_ini_set $HESTIA/conf/modules.conf 'ftp' 'enabled' '0'
    osal_ini_set $HESTIA/conf/modules.conf 'ftp' 'variant' ''
    osal_ini_set $HESTIA/conf/modules.conf 'ftp' 'version' '0'

    exit 0
}

# If this files is _not_ being sourced, act immediately
# (otherise, wait for hestia cli to call the main function)
[[ $_ == $0 ]] && hestia_module_vsftpd_remove $@