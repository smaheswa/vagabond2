set path=src/**

command! Tags !ctags -R libgui/* libsrc/*
command! Ninja :wa|!ninja -C build/current vagabond
command! Winja :wa|!ninja -C build/website
command! Unit :wa|!cd build/current; meson test --suite=unit
command! Integration :wa|!cd build/current; meson test --suite=integration

" `u to compile unit tests
:imap `u :Tinja
:nmap `u :Tinja


command! Doxy !doxygen Doxyfile

function! MakeTest()
	let testname = input("name your test: ")
	:execute "!./make_test " . testname
	:execute "edit " . fnameescape("tests/" . testname . ".cpp")
endfunction

command Test call MakeTest()
