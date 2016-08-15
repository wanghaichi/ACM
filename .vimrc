set nu ai ci si mouse=a ts=4 sts=4 sw=4
set backspace=indent,eol,start
syntax enable

syntax on

set showmatch
inoremap ( ()<ESC>i
inoremap { {}<ESC>i
inoremap [ []<ESC>i
inoremap " ""<ESC>i
inoremap ' ''<ESC>i

let &termencoding=&encoding
set fileencodings=utf-8,gbk

colorscheme slate

"SET Comment START
"autocmd BufNewFile *.php,*.js,*.cpp exec ":call SetComment()" |normal 10Go
autocmd BufNewFile *.cpp exec ":call SetComment()" |normal 44Go

func SetComment()
	"if expand("%:e") == 'php'
	"	call setline(1, "<?php")
	"elseif expand("%:e") == 'js'
	"	call setline(1, '//JavaScript file')
	"elseif expand("%:e") == 'cpp'
	"	call setline(1, '//C++ file')
	"endif
	call setline(1, '/*************************************************************')
	call setline(2, '')
	call setline(3, 'FILENAME:                   '.expand("%"))
	call setline(4, '')
	call setline(5, 'AUTHOR:         Hardy - wanghaichi@twtstudio.com')
	call setline(6, '')
	call setline(7, 'CREATE:                '.strftime("%Y-%m-%d %H:%M:%S"))
	call setline(8, '')
	call setline(9, 'LAST MODIFIED:         '.strftime("%Y-%m-%d %H:%M:%S"))
	call setline(10, '')
	call setline(11, 'ID: ')
	call setline(12, '')
	call setline(13, 'TYPE: ')
	call setline(14, '')
	call setline(15, 'DETAIL: ')
	call setline(16, '')
	call setline(17, 'TATICS: ')
	call setline(18, '')
	call setline(19, '************************************************************/')
	call setline(20, '')
	call setline(21, '#include <iostream>')
	call setline(22, '#include <cstdio>')
	call setline(23, '#include <algorithm>')
	call setline(24, '#include <cstring>')
	call setline(25, '#include <vector>')
	call setline(26, '#include <cmath>')
	call setline(27, '#include <queue>')
	call setline(28, '#include <stack>')
	call setline(29, '#include <map>')
	call setline(30, '')
	call setline(31, '#define MAX(a, b) (a > b ? a : b)')
	call setline(32, '#define MIN(a, b) (a > b ? b : a)')
	call setline(33, '#define CL(a) memset(a, 0, sizeof(a))')
	call setline(34, '')
	call setline(35, 'using namespace std;')
	call setline(36, '')
	call setline(37, 'typedef long long ll;')
	call setline(38, '')
	call setline(39, 'const int inf = 1e9+7;')
	call setline(40, 'const int mod = 1e9+7;')
	call setline(41, 'const int maxn = 1e6+7;')
	call setline(42, '')
	call setline(43, 'int main()')
	call setline(44, '{')
	call setline(45, '')
	call setline(46, '')
	call setline(47, '	return 0;')
	call setline(48, '}')
	call setline(49, '')
"	call append(10, '')
endfunc

"map <F2> :call SetComment()<CR>:10<CR>o
"SET Comment END

"SET Last Modified Time START
func DataInsert()
	call cursor(9,1)
	if search ('LAST MODIFIED') != 0
		let line = line('.')
		call setline(line, 'LAST MODIFIED:         '.strftime("%Y-%m-%d %H:%M:%S"))
	endif
endfunc
"autocmd FileWritePre,BufWritePre *.php,*.js,*.cpp ks|call DataInsert() |'s
autocmd FileWritePre,BufWritePre *.cpp ks|call DataInsert() |'s

"SET Last Modified Time END
