#!/bin/bash

# set -x

OSSL="$HOME/code/openssl"
APA="$HOME/code/httpd"

# make directories for lighttpd stuff if needed
mkdir -p $OSSL/esnistuff/apache/logs
mkdir -p $OSSL/esnistuff/apache/www
mkdir -p $OSSL/esnistuff/apache/baz

# check for/make a home page for example.com and other virtual hosts
if [ ! -f $OSSL/esnistuff/apache/www/index.html ]
then
    cat >$OSSL/esnistuff/apache/www/index.html <<EOF

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>example.com apache top page.</title>
</head>
<!-- Background white, links blue (unvisited), navy (visited), red
(active) -->
<body bgcolor="#FFFFFF" text="#000000" link="#0000FF"
vlink="#000080" alink="#FF0000">
<p>This is the pretty dumb top page for testing. </p>

</body>
</html>

EOF
fi

# check for/make a slightly different home page for baz.example.com
if [ ! -f $OSSL/esnistuff/apache/baz/index.html ]
then
    cat >$OSSL/esnistuff/apache/baz/index.html <<EOF

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>baz.example.com apache top page.</title>
</head>
<!-- Background white, links blue (unvisited), navy (visited), red
(active) -->
<body bgcolor="#FFFFFF" text="#000000" link="#0000FF"
vlink="#000080" alink="#FF0000">
<p>This is the pretty dumb top page for baz.example.com testing. </p>

</body>
</html>

EOF
fi

export LD_LIBRARY_PATH=$OSSL
PIDFILE=$OSSL/esnistuff/apache/httpd.pid
# Kill off old processes from the last test
if [ -f $PIDFILE ]
then
    echo "Killing old httpd in process `cat $PIDFILE`"
    kill `cat $PIDFILE`
    rm -f $PIDFILE
else 
    echo "Can't find $PIDFILE - tring killall httpd"
    killall httpd
fi
# check if some process was left over after gdb or something

# kill off other processes
procs=`ps -ef | grep httpd | grep -v grep | awk '{print $2}'`
for proc in $procs
do
    echo "Killing old httpd (from gdb maybe) in $proc"
    kill -9 $proc
done

# give the n/w a chance so 9443 is free to use
sleep 2

# set to use valgrind, unset to not
# VALGRIND="valgrind --leak-check=full --show-leak-kinds=all"
# VALGRIND="valgrind --leak-check=full "
#VALGRIND="valgrind "
VALGRIND=""

# Set/unset to detach or run in foreground
FGROUND=""
# FGROUND="-DFOREGROUND "

echo "Executing: $VALGRIND $APA/httpd -f $OSSL/esnistuff/apachemin.conf"
# move over there to run code, so config file can have relative paths
cd $OSSL/esnistuff
$VALGRIND $APA/httpd -d . -f apachemin.conf $FGROUND
cd - 

