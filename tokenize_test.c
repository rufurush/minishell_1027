/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:42:32 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/15 16:04:22 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "minishell.h"
// // tok_test.c
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// /* ====== あなたの自作関数（そのまま or 既存のヘッダから持ってきてOK） ====== */
// int is_metachar(char c)
// {
//     if(c == '|' || c == '<' || c == '>' || c == '&')
//         return(1);
//     else
//         return(0);
// }

// int is_quote(char c)
// {
//     if(c == '\'' || c == '"')
//         return(1);
//     else
//         return(0);
// }

// int is_space(char c)
// {
//     if(c == ' ' || c == '\t')
//         return(1);
//     else
//         return(0);
// }

// /* メタの長さだけ進める（あなたの関数） */
// void	meta_token_end(char *line, size_t *index)
// {
// 	if(is_metachar(line[*index]))
// 	{
// 		if((line[*index] == '<' && line[*index + 1] == '<') || (line[*index] == '>' && line[*index + 1] == '>'))
//         {
//             (*index) += 2;
//             return ;
//         }
//         (*index)++;
//         return ;
// 	}
// 	else
// 		return;
// }

// /* WORD の終端まで進める（あなたの関数） */
// void    token_end(char *line,size_t *index)
// {
//     int s_quote;
//     int d_quote;
//     size_t start;

//     s_quote = 0;
//     d_quote = 0;
//     start = *index;

//     if(line[start] == '\'')
//         s_quote = 1;
//     if(line[start] == '"')
//         d_quote = 1;
//     if(d_quote || s_quote)
//         (*index)++;
//     while(line[*index] != '\0')
//     {
//         if(line[*index] == '\'' && d_quote != 1)
//         {
//             if(s_quote == 0)
//                 s_quote = 1;
// 			else if(is_space(line[*index + 1]) && (s_quote != 1))
// 				s_quote = 0;
//             else
// 				s_quote = 0;
//         }
//         else if(line[*index] == '"' && s_quote != 1)
//         {
//             if(d_quote == 0)
//                 d_quote = 1;
// 			else if(is_space(line[*index + 1]) && (d_quote == 0))
// 				d_quote = 0;
//             else
// 				d_quote = 0;
//         }
//         if(s_quote == 0 && d_quote == 0)
//         {
//             if(is_space(line[*index]) || is_metachar(line[*index]))
//                 return ;
//         }
//         (*index) += 1;
//     }
// }

// /* ====== ここからテスト用の最小限の“つなぎ”だけ ====== */

// typedef enum e_toktype {
//     T_WORD,
//     T_PIPE,      // |
//     T_INPUT,     // <
//     T_OUTPUT,    // >
//     T_HEREDOC,   // <<
//     T_APPEND,    // >>
//     T_AMPERSAND  // & （ボーナスなら適宜）
// } t_toktype;

// static const char *type_name(t_toktype t){
//     switch(t){
//         case T_WORD: return "WORD";
//         case T_PIPE: return "PIPE";
//         case T_INPUT: return "INPUT";
//         case T_OUTPUT: return "OUTPUT";
//         case T_HEREDOC: return "HEREDOC";
//         case T_APPEND: return "APPEND";
//         case T_AMPERSAND: return "AMPERSAND";
//     }
//     return "?";
// }

// /* メタのスライス（内容）から型を決めるだけ。分割は meta_token_end に任せる。 */
// static t_toktype meta_type_from_slice(const char *s, size_t len)
// {
//     if (len==2 && s[0]=='<') return T_HEREDOC;
//     if (len==2 && s[0]=='>') return T_APPEND;
//     if (len==1 && s[0]=='<') return T_INPUT;
//     if (len==1 && s[0]=='>') return T_OUTPUT;
//     if (len==1 && s[0]=='|') return T_PIPE;
//     if (len==1 && s[0]=='&') return T_AMPERSAND; // 必要なら
//     return T_WORD; // ここに来ない想定
// }

// /* 安全な部分複製 */
// static char *dup_range(const char *s, size_t start, size_t len)
// {
//     char *out = (char*)malloc(len+1);
//     if(!out) return NULL;
//     memcpy(out, s+start, len);
//     out[len] = '\0';
//     return out;
// }

// /* トークン1個を表示（位置情報も出すとデバッグしやすい） */
// static void print_one_token(const char *line, size_t start, size_t end, t_toktype ty)
// {
//     char *seg = dup_range(line, start, end-start);
//     if (!seg) { fprintf(stderr, "alloc error\n"); return; }
//     printf("  - [%s] \"%s\"  (pos %zu..%zu)\n", type_name(ty), seg, start, end ? (end-1) : start);
//     free(seg);
// }

// /* あなたの関数だけで「読み進めながら」トークン列を吐く */
// static void test_tokenize_with_your_funcs(const char *line)
// {
//     size_t n = strlen(line);
//     size_t i = 0;

//     printf("INPUT: [%s]\n", line);
//     printf("TOKENS:\n");

//     while (i < n)
//     {
//         /* 1) 先頭空白スキップ（非クォートの空白のみ） */
//         while (i < n && is_space(line[i])) i++;
//         if (i >= n) break;

//         /* 2) メタなら、あなたの meta_token_end で長さだけ進める → そのスライスを出力 */
//         if (is_metachar(line[i])) {
//             size_t start = i;
//             size_t before = i;
//             meta_token_end((char*)line, &i);          // ← あなたの関数で i が進む
//             size_t oplen = i - before;                // 1 or 2
//             if (oplen == 0) { // 念のため
//                 i++; continue;
//             }
//             t_toktype ty = meta_type_from_slice(line + start, oplen);
//             print_one_token(line, start, start + oplen, ty);
//             continue;
//         }

//         /* 3) それ以外は WORD：あなたの token_end で“区切り直前”まで進める */
//         size_t start = i;
//         token_end((char*)line, &i);                   // ← あなたの関数で i が進む（区切りは消費しないはず）
//         if (i > start)
//             print_one_token(line, start, i, T_WORD);
//         /* 次ループで、止まった位置の区切り（空白 or メタ）を再処理 */
//     }
//     puts("");
// }

// // /* 可視化（任意）：トークン境界を ^ でマークして位置を見やすくする */
// // static void visualize_boundaries(const char *line)
// // {
// //     size_t n = strlen(line);
// //     size_t i = 0;
// //     char *marks = (char*)calloc(n+1, 1);
// //     if (!marks) return;

// //     while (i < n)
// //     {
// //         while (i < n && is_space(line[i])) i++;
// //         if (i >= n) break;

// //         size_t start = i;

// //         if (is_metachar(line[i])) {
// //             //size_t before = i;
// //             meta_token_end((char*)line, &i);
// //             size_t end = i;
// //             if (end > start) marks[start] = '^', marks[end-1] = '^';
// //             continue;
// //         }
// //         token_end((char*)line, &i);
// //         size_t end = i;
// //         if (end > start) marks[start] = '^', marks[end-1] = '^';
// //     }

// //     printf("LINE : %s\n", line);
// //     printf("MARKS: ");
// //     for (size_t k=0; k<n; ++k) {
// //         if (marks[k]) putchar('^');
// //         else putchar((line[k]=='\t') ? 't' : ' ');
// //     }
// //     putchar('\n'); putchar('\n');
// //     free(marks);
// // }

// /* ====== テストエントリ ====== */
// int main(void)
// {
//     const char *cases[] = {
//         "echo hello world",
//         "echo   \"a b\"   'c d'",
//         "avbd'aasda'",
//         "'abc'def",
//         "\"a|b\"  c|d",
//         "   \"x y\"z   ",
//         "foo'bar'  \"baz\"qux",
//         "\"unterminated",
//         "<infile cat | wc -l > outfile",
//         "echo>a",
//         "a|b|c",
//         "cat<<EOF",
//         "echo>>out",
//         "cmd>>>file",
//         "<<>>",
//         "<|>",
//         "\"a|b c|d\"",
//         "grep \"a b\" <\"in file\" >\"out file\"",
//         "cat << 'EOF'",
//         "cat <<EOF|wc",
//         "echo \"$USER $HOME\"",
//                 "echo hello world",
//         "echo   \"a b\"   'c d'",
//         "avbd'aasda'",
//         "'abc'def",
//         "\"a|b\"  c|d",         /* 今回はメタ無視、後で対応 */
//         "   \"x y\"z   ",
//         "foo'bar'  \"baz\"qux",
//         "single'quote end'",
//         "\"unterminated",
// 		"<infile cat | wc -l > outfile",
// 		"'ab'\"cd\"ef",
// 		"a \"b c\" d",
// 		"a''b",
// 		"''",
// 		"\"a'b\"c'd",
// 		"\"'a'\"",
// 		"''\"\"''",
// 		"\"abc",
// 		"a 'b c",
// 		"echo>a",
// 		"a|b|c",
// 		"cat<<EOF",
// 		"echo>>out",
// 		"cmd>>>file",
// 		"<<>>",
// 		"<|>",
// 		"\"a|b c|d\"",
// 		"'>' \"<\" \"|\" \">>\"'",
// 		"        a b         ",
// 		"\"x y\"z",
// 		"a\t\tb",
// 		"cat < in | grep foo | wc -l > out",
// 		"grep \"a b\" <\"in file\" >\"out file\"",
// 		"cat << 'EOF'",
// 		"cat <<EOF|wc",
// 		"echo \"$USER $HOME\"",
//         NULL
//     };

//     for (int i = 0; cases[i]; ++i) {
//         test_tokenize_with_your_funcs(cases[i]);
//         // 境界の可視化を見たいときは下を有効化
//         // visualize_boundaries(cases[i]);
//     }
//     return 0;
//}
