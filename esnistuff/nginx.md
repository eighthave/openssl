
# Playing about with nginx

## Clone, Build and Run

Note that PRs against the github repo aren't desired. But I didn't check out
what they do desire yet:-)

            $ cd code
            $ git clone https://github.com/sftcd/nginx.git
            $ cd nginx
            $ ./auto/configure --with-debug --prefix=nginx --with-http_ssl_module --with-openssl=$HOME/code/openssl
            $ make
            ... go for coffee ...

- That seems to re-build openssl (inc. a ``make config; make clean``) within
  $HOME/code/openssl for some reason.
- And that includes creating a new "$HOME/code/openssl/.openssl" directory
  where it puts files from $HOME/openssl/include, static libraries and an
  openssl command line binary.
- And it doesn't detect if I change code e.g. $HOME/code/openssl/ssl/esni.c or
  $HOME/code/openssl/include/openssl/esni.h
- Odd. 

Other than that the "--prefix=nginx" setting there is to match our [testnginx.sh](testnginx.sh)
script.  The [nginxmin.conf](nginxmin.conf) file that uses has a minimal configuration to 
match out localhost test setup.

            $ cd $HOME/code/openssl/esnistuff
            $ ./testnginx.sh
            ... prints stuff, spawns server and exits ...
            $ curl  --connect-to baz.example.com:443:localhost:5443 https://baz.example.com/index.html --cacert cadir/oe.csr 
            
            <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
                "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
            <html xmlns="http://www.w3.org...

## ESNI configuration

I added an ESNI key directory configuration setting that can be within the ``http``
stanza (and maybe elsewhere too, I don't fully understand all that yet;-). Then,
with a bit of generic parameter handling and the addition of a ``load_esnikeys()`` 
function that's pretty much as done for [lighttpd](./lighttpd), ESNI... just worked!

You can see that configuration setting, called ``ssl_esnikeydir`` in our
test [nginxmin.confg](nginxmin.conf).

            $ ./testnginx.sh
            ... stuff ...
            $ /testclient.sh -p 5443 -s localhost -H baz.example.com -c example.net -P esnikeydir/ff03.pub
            Running ./testclient.sh at 20191012-125357
            ./testclient.sh Summary: 
            Looks like 1 ok's and 0 bad's.

The only ESNI-related logging is when keys are loaded or re-loaded which looks
like:

            2019/10/12 14:32:13 [notice] 16953#0: load_esnikeys, worked for: /home/stephen/code/openssl/esnistuff/esnikeydir/ff01.pub
            2019/10/12 14:32:13 [notice] 16953#0: load_esnikeys, worked for: /home/stephen/code/openssl/esnistuff/esnikeydir/e3.pub
            2019/10/12 14:32:13 [notice] 16953#0: load_esnikeys, worked for: /home/stephen/code/openssl/esnistuff/esnikeydir/ff03.pub
            2019/10/12 14:32:13 [notice] 16953#0: load_esnikeys, worked for: /home/stephen/code/openssl/esnistuff/esnikeydir/e2.pub
            2019/10/12 14:32:13 [notice] 16953#0: load_esnikeys, total keys loaded: 4

Note that even though I see 3 occurrences of those log lines, we only end up
with 4 keys loaded as the library function checks that the files are the same.

## Reloading ESNI keys

Nginx will reload its configuration if you send it a SIGHUP signal. That's easier
to use than we saw with lighttp, so if you change the set of keys in the ESNI key
directory then you can:

            $ kill -SIGHUP `cat nginx/logs/nginx.pid`

...and that does cause the ESNI key files to be reloaded nicely. If you add and
remove key files, that all seems ok, I guess because nginx cleans up (worker)
processses that have the keys in memory. (That's nicely a lot easier than with 
lighttpd:-) 


## Improvements...

- Check with valgrind we're not leaking! 
- Portability: there's an ``ngx_read_dir()`` wrapper for ``readdir()`` that
  really needs to be used.
- It'd be better if the ``ssl_esnikeydir`` were a "global" setting probably (like
  ``error_log``) but when I need to figure out how to get that to work still. For
  now it seems it has to be inside the ``http`` stanza, and one occurrence of 
  the setting causes ``load_esnikeys()`` to be called three times in our test
  setup which seems a little off. (It's ok though as we only really store keys
  from different files.)


