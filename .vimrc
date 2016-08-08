set nu ai ci si mouse=a ts=4 sts=4 sw=4
set showmatch
inoremap ( ()<ESC>i
inoremap { {}<ESC>i
inoremap [ []<ESC>i
inoremap " ""<ESC>i
inoremap ' ''<ESC>i

map <insert> <S-i>//<Esc>j
map <C-F12> <S-i><delete><delete><Esc>j

map<F5> :call CR()<CR>
func! CR()
exec "w"
exec "!g++ % -o %<"
exec "! ./%<"
endfunc

map<F2> :call SetTitle()<CR>
func SetTitle()
let l = 0
let l = l + 1 | call setline(l,'/*')
let l = l + 1 | call setline(l,'Author Hardy')
let l = l + 1 | call setline(l,'*/')
endfunc

let &termencoding=&encoding
set fileencodings=utf-8,gbk



