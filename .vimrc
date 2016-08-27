let mapleader=";"

set nu ai ci si mouse=a ts=4 sts=4 sw=4

set backspace=indent,eol,start

" 自适应不同语言的智能缩进
filetype indent on
" 将制表符扩展为空格
set expandtab
" 设置编辑时制表符占用空格数
set tabstop=4
" 设置格式化时制表符占用空格数
set shiftwidth=4
" 让 vim 把连续数量的空格视为一个制表符
set softtabstop=4

" 总是显示状态栏
set laststatus=2
" 显示光标当前位置
set ruler
" 开启行号显示
set number
" 高亮显示当前行/列
"set cursorline
"set cursorcolumn
" 高亮显示搜索结果
set hlsearch

" 基于缩进或语法进行代码折叠
"set foldmethod=indent
set foldmethod=syntax
" 启动 vim 时关闭折叠代码
set nofoldenable

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

" 开启实时搜索功能
set incsearch
" 搜索时大小写不敏感
set ignorecase
" 关闭兼容模式
set nocompatible
" vim 自身命令行模式智能补全
set wildmenu

" 禁止光标闪烁
set gcr=a:block-blinkon0
" 禁止显示滚动条
set guioptions-=l
set guioptions-=L
set guioptions-=r
set guioptions-=R
" 禁止显示菜单和工具条
set guioptions-=m
set guioptions-=T

" 将外部命令 wmctrl 控制窗口最大化的命令行参数封装成一个 vim 的函数
fun! ToggleFullscreen()
    call system("wmctrl -ir " . v:windowid . " -b toggle,fullscreen")
endf
" 全屏开/关快捷键
map <silent> <F11> :call ToggleFullscreen()<CR>
" 启动 vim 时自动全屏
autocmd VimEnter * call ToggleFullscreen()

"SET Comment START
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

" vundle 环境设置
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
" vundle 管理的插件列表必须位于 vundle#begin() 和 vundle#end() 之间
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'altercation/vim-colors-solarized'
Plugin 'tomasr/molokai'
Plugin 'vim-scripts/phd'
Plugin 'Lokaltog/vim-powerline'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'nathanaelkane/vim-indent-guides'
Plugin 'derekwyatt/vim-fswitch'
Plugin 'kshenoy/vim-signature'
Plugin 'majutsushi/tagbar'
Plugin 'vim-scripts/indexer.tar.gz'
Plugin 'vim-scripts/DfrankUtil'
Plugin 'vim-scripts/vimprj'
Plugin 'dyng/ctrlsf.vim'
Plugin 'terryma/vim-multiple-cursors'
Plugin 'scrooloose/nerdcommenter'
Plugin 'vim-scripts/DrawIt'
Plugin 'SirVer/ultisnips'
Plugin 'Valloric/YouCompleteMe'
Plugin 'derekwyatt/vim-protodef'
Plugin 'scrooloose/nerdtree'
Plugin 'fholgado/minibufexpl.vim'
Plugin 'gcmt/wildfire.vim'
Plugin 'sjl/gundo.vim'
Plugin 'Lokaltog/vim-easymotion'
Plugin 'suan/vim-instant-markdown'
Plugin 'lilydjwg/fcitx.vim'
" 插件列表结束
call vundle#end()
filetype plugin indent on

let g:Powerline_colorscheme='solarized256'

" 随 vim 自启动
let g:indent_guides_enable_on_vim_startup=1
" 从第二层开始可视化显示缩进
let g:indent_guides_start_level=2
" 色块宽度
let g:indent_guides_guide_size=1
" 快捷键 i 开/关缩进可视化
:nmap <silent> <Leader>i <Plug>IndentGuidesToggle

" *.cpp 和 *.h 间切换
nmap <silent> <Leader>sw :FSHere<cr>

" 设置 tagbar 子窗口的位置出现在主编辑区的左边 
let tagbar_left=1 
" 设置显示／隐藏标签列表子窗口的快捷键。速记：identifier list by tag
nnoremap <Leader>ilt :TagbarToggle<CR> 
" 设置标签子窗口的宽度 
let tagbar_width=32 
" tagbar 子窗口中不显示冗余帮助信息 
let g:tagbar_compact=1
" 设置 ctags 对哪些代码标识符生成标签
let g:tagbar_type_cpp = {
    \ 'kinds' : [
         \ 'c:classes:0:1',
         \ 'd:macros:0:1',
         \ 'e:enumerators:0:0', 
         \ 'f:functions:0:1',
         \ 'g:enumeration:0:1',
         \ 'l:local:0:1',
         \ 'm:members:0:1',
         \ 'n:namespaces:0:1',
         \ 'p:functions_prototypes:0:1',
         \ 's:structs:0:1',
         \ 't:typedefs:0:1',
         \ 'u:unions:0:1',
         \ 'v:global:0:1',
         \ 'x:external:0:1'
     \ ],
     \ 'sro'        : '::',
     \ 'kind2scope' : {
         \ 'g' : 'enum',
         \ 'n' : 'namespace',
         \ 'c' : 'class',
         \ 's' : 'struct',
         \ 'u' : 'union'
     \ },
     \ 'scope2kind' : {
         \ 'enum'      : 'g',
         \ 'namespace' : 'n',
         \ 'class'     : 'c',
         \ 'struct'    : 's',
         \ 'union'     : 'u'
     \ }
\ }

