#!/usr/bin/env ruby

def usage
	puts <<TXT
#{__FILE__}: usage: #{__FILE__} ACTION
Available actions:
	build		Build library
	clean		Clean binaries
	install		Install binaries
	uninstall	Uninstall binaries
TXT
end

prefix = "/usr"
if ENV.has_key? "PREFIX"
	prefix = ENV["PREFIX"]
end

case ARGV[0]
when nil
	usage
	exit! 1
when "build"
	print `mkdir -p build/include build/lib`
	print `gcc -fPIC -shared -Isrc -o build/lib/libdystring.so src/dystring/dystring.c src/dystring/reader.c src/dystring/writer.c`
	print `cp -r src/. build/include/`
	print `bash -c "shopt -s globstar; rm -f build/include/**/**/**/**.c"`
when "clean"
	print `rm -rf build`
when "install"
	print `cp -r build/. #{prefix}/`
when "uninstall"
	print `rm -rf #{prefix}/include/dystring #{prefix}/lib/libdystring.so`
else
	$stderr.puts "#{__FILE__}: unknown action: \"#{ARGV[0]}\""
	exit! 1
end
exit! 0
