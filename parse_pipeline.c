/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:30:39 by kotadashiru       #+#    #+#             */
/*   Updated: 2025/10/26 14:27:59 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redir(t_token_type type)
{
    return (type == INPUT || type == OUTPUT || type == APPEND);
}

void    parse_command_syntax_err(t_token_type type)
{
    if(type == AND)
    {
        ft_putstr_fd("syntax error near unexpected token '&&'\n",2);
        return;
    }
    else
    {
        ft_putstr_fd("syntax err\n",2);
        return;
    }
}

int cmd_push_arg_node(t_ast *cmd,const char *str)
{
    t_arg *new;
    t_arg *tmp;

    new = malloc(sizeof(t_arg));
    if(!new)
        return(0);
    new->value = ft_strdup(str);
    if(!new->value)
    {
        free(new);
        return(0);
    }
    new->next = NULL;
    if(!cmd->arg_list)
        cmd->arg_list = new;
    else
    {
        tmp = cmd->arg_list;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return(1);
}

t_redir *make_heredoc_node(const char *delim, int quoted) {
    t_redir *r = malloc(sizeof(*r));
    if (!r) return NULL;
    r->kind = HEREDOC;
    r->filename = NULL;
    r->delim = ft_strdup(delim);
    r->quoted = quoted;
    r->next = NULL;
    return r;
}

static  void    append_redir(t_ast *cmd, t_redir *node)
{
    t_redir *p;

    if(!cmd->redirs)
    {
        cmd->redirs = node;
        return;
    }
    p = cmd->redirs;
    while(p->next)
        p = p->next;
    p->next = node;
}

static t_redir *make_redir_node(t_token_type kind,const char *filename,int quoted)
{
    t_redir *node;

    node = malloc(sizeof(t_redir));
    if(!node)
        return(NULL);
    node->kind = kind;
    node->filename = ft_strdup(filename);
    if(!node->filename)
    {
        free(node);
        return(NULL);
    }
    node->quoted = quoted;
    node->next = NULL;
    return(node);
}

int   parse_redirection(t_ast *cmd, t_token_type kind, t_token_list *content)
{
    t_redir *node;
    int     quoted;

    if(!(kind == INPUT || kind == OUTPUT || kind == APPEND || kind == HEREDOC))
        return(0);
    if(!content || content->type != WORD)
        return(0);
    quoted = 0;
    node = make_redir_node(kind,content->content,quoted);
    if(!node)
        return(0);
    append_redir(cmd,node);
    return(1);
}

t_ast *ast_new_cmd()
{
    t_ast *node;

    node = (malloc(sizeof(t_ast)));
    if(!node)
        return(NULL);

    node->type = NODE_CMD;
    node->argv = NULL;
    node->arg_list = NULL;
    node->redirs = NULL;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

static void free_arg_list_a(t_arg *a)
{
    while (a) 
    {
         t_arg *n = a->next; 
        free(a->value); 
        free(a); 
        a = n; 
    }
}

static void free_redirs_a(t_redir *r)
{
    while (r) 
    { 
        t_redir *n = r->next;
        free(r->filename);
        free(r); 
        r = n; 
    }
}

void ast_free_a(t_ast *n)
{
    if (!n)
        return;
    ast_free_a(n->left);
    ast_free_a(n->right);
    if (n->argv) 
    {
        for (int i = 0; n->argv[i]; ++i)
           free(n->argv[i]);
        free(n->argv);
    }
    free_arg_list_a(n->arg_list);
    free_redirs_a(n->redirs);
    free(n);
}

char **list_to_argv(t_arg *list)
{
    size_t len = 0; for (t_arg *p=list; p; p=p->next) ++len;
    char **argv = malloc(sizeof(char*)*(len+1));
    if (!argv) return NULL;
    size_t i=0;
    for (t_arg *p=list; p; p=p->next) argv[i++] = ft_strdup(p->value);
    argv[i] = NULL;
    return argv;
}

t_ast   *parse_command(t_token_list **cur)
{
    t_ast           *cmd;
    t_token_type    kind;
    int             seen;

    seen = 0;
    cmd = ast_new_cmd();//コマンドの初期化
    while(*cur && (*cur)->type != PIPE)
    {
        if((*cur)->type == WORD)
        {
            if(!cmd_push_arg_node(cmd,(*cur)->content))
            {
                ast_free_a(cmd);
                return(NULL);
            }
            *cur = (*cur)->next;
            seen = 1;
        }
        else if((*cur)->type == HEREDOC)
        {
            *cur = (*cur)->next;
            if (!*cur || (*cur)->type != WORD)
                return(ft_putstr_fd("delimiter required",2), NULL);
            append_redir(cmd,make_heredoc_node((*cur)->content,(*cur)->quoted));
            *cur = (*cur)->next;
            seen = 1;
            continue;
        }
        else if(is_redir((*cur)->type))
        {
            kind = (*cur)->type;
            *cur = (*cur)->next;
            if(!*cur || (*cur)->type != WORD)
            {
                ft_putstr_fd("syntax error filename required\n",2);
                ast_free_a(cmd);
                return(NULL);
            }
            if(!parse_redirection(cmd,kind,*cur))
            {
                ast_free_a(cmd);
                return(NULL);
            }
            *cur = (*cur)->next;
            seen = 1;
        }
        else
        {
            parse_command_syntax_err((*cur)->type);
            ast_free_a(cmd);
            return(NULL);
        }
    }
    if(!seen)
    {
        ast_free_a(cmd);
        return(NULL);
    }
    cmd->argv = list_to_argv(cmd->arg_list);
    return(cmd);
}

t_ast   *ast_new_pipe(t_ast *left,t_ast *right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if(!node)
        return(NULL);
    node->type = NODE_PIPE;
    node->argv = NULL;
    node->arg_list = NULL;
    node->redirs = NULL;
    node->left = left;
    node->right = right;
    return(node);
}

void consume(t_token_list **cur, t_token_type expected)
{
    if (*cur == NULL)
        return;

    if ((*cur)->type == expected)
        *cur = (*cur)->next;
    else
        ft_putstr_fd("parse error: unexpected token\n", 2);
}

t_ast   *parse_pipeline(t_token_list **cur)
{
    t_ast   *left;
    t_ast   *right;

    left = parse_command(cur);
    if(!left)
    {
        if(*cur && (*cur)->type == PIPE)
            ft_putstr_fd("syntax error near unexpected token `|'\n",2);
        else
            ft_putstr_fd("syntax error near unexpected token `newline'\n",2);
        return(NULL);
    }
    while(*cur && (*cur)->type == PIPE)
    {
        consume(cur,PIPE);
        right = parse_command(cur);
        if(!right)
        {
            ft_putstr_fd("syntax error near unexpected token `newline'\n",2);
            ast_free_a(left);
            return(NULL);
        }
        left = ast_new_pipe(left,right);
    }
    return(left);
}

// // ===== list_to_argv.c =====

// // ===== test_helpers.c =====
// #include "minishell.h"

// // --- トークン生成 ---
// t_token_list *tok(t_token_type type, const char *s) {
//     t_token_list *t = malloc(sizeof(*t));
//     if (!t) return NULL;
//     t->type = type;
//     t->content = s ? ft_strdup(s) : NULL;
//     t->next = NULL;
//     return t;
// }

// t_token_list *push_tok(t_token_list **head, t_token_type type, const char *s) {
//     t_token_list *n = tok(type, s);
//     if (!*head) *head = n;
//     else {
//         t_token_list *p = *head;
//         while (p->next) p = p->next;
//         p->next = n;
//     }
//     return n;
// }

// void free_tokens(t_token_list *t) {
//     while (t) { t_token_list *n = t->next; free(t->content); free(t); t = n; }
// }

// // --- AST 表示（デバッグ用） ---
// static void indent(int d){ while(d--) write(1,"  ",2); }

// static const char* redir_str(t_token_type k){
//     if (k==INPUT) return "<";
//     if (k==OUTPUT) return ">";
//     if (k==APPEND) return ">>";
//     if (k==HEREDOC) return "<<";
//     return "?";
// }

// void print_ast(const t_ast *n, int depth) {
//     if (!n){ indent(depth); printf("(NULL)\n"); return; }
//     if (n->type == NODE_PIPE) {
//         indent(depth); printf("PIPE\n");
//         print_ast(n->left,  depth+1);
//         print_ast(n->right, depth+1);
//         return;
//     }
//     // NODE_CMD
//     indent(depth); printf("CMD\n");
//     // argv
//     indent(depth+1); printf("argv:");
//     if (n->argv) {
//         for (int i=0; n->argv[i]; ++i) printf(" [%s]", n->argv[i]);
//     }
//     printf("\n");
//     // redirs
//     indent(depth+1); printf("redirs:");
//     t_redir *r = n->redirs;
//     if (!r) { printf(" (none)\n"); }
//     else {
//         printf("\n");
//         for (; r; r=r->next) {
//             indent(depth+2);
//             printf("%s %s\n", redir_str(r->kind), r->filename);
//         }
//     }
// }

// // --- AST 解放 ---
// void free_arg_list(t_arg *a){
//     while(a){ t_arg *n=a->next; free(a->value); free(a); a=n; }
// }

// void free_redirs(t_redir *r){
//     while(r){ t_redir *n=r->next; free(r->filename); free(r); r=n; }
// }

// void free_ast(t_ast *n){
//     if (!n) return;
//     free_ast(n->left);
//     free_ast(n->right);
//     if (n->argv){ for (int i=0; n->argv[i]; ++i) free(n->argv[i]); free(n->argv); }
//     free_arg_list(n->arg_list);
//     free_redirs(n->redirs);
//     free(n);
// }

// // ===== test_parser.c =====
// #include "minishell.h"

// // プロトタイプ（あなたの実装）
// t_ast *parse_pipeline(t_token_list **cur);
// char **list_to_argv(t_arg *list);
// void   print_ast(const t_ast *n, int depth);
// void   free_tokens(t_token_list *t);
// void   free_ast(t_ast *n);
// t_token_list *push_tok(t_token_list **head, t_token_type type, const char *s);

// static void run_case(const char *title, t_token_list *tokens) {
//     printf("=== %s ===\n", title);
//     t_token_list *cur = tokens;
//     t_ast *root = parse_pipeline(&cur);
//     if (!root) {
//         printf("[PARSE ERROR]\n\n");
//     } else {
//         print_ast(root, 0);
//         printf("\n");
//         free_ast(root);
//     }
//     free_tokens(tokens);
// }

// int main(void)
// {
//     // 1) echo hello
//     {
//         t_token_list *t=NULL;
//         push_tok(&t, WORD, "echo");
//         push_tok(&t, WORD, "hello");
//         run_case("echo hello", t);
//     }

//     // 2) echo a > out
//     {
//         t_token_list *t=NULL;
//         push_tok(&t, WORD, "echo");
//         push_tok(&t, WORD, "a");
//         push_tok(&t, OUTPUT, NULL);
//         push_tok(&t, WORD, "out");
//         run_case("echo a > out", t);
//     }

//     // 3) cat < in | grep x >> out
//     {
//         t_token_list *t=NULL;
//         push_tok(&t, WORD, "cat");
//         push_tok(&t, INPUT, NULL);
//         push_tok(&t, WORD, "in");
//         push_tok(&t, PIPE, NULL);
//         push_tok(&t, WORD, "grep");
//         push_tok(&t, WORD, "x");
//         push_tok(&t, APPEND, NULL);
//         push_tok(&t, WORD, "out");
//         run_case("cat < in | grep x >> out", t);
//     }

//     // 4) 先頭パイプ: | ls  → エラー
//     {
//         t_token_list *t=NULL;
//         push_tok(&t, PIPE, NULL);
//         push_tok(&t, WORD, "ls");
//         run_case("| ls", t);
//     }

//     // 5) 末尾パイプ: ls |  → エラー
//     {
//         t_token_list *t=NULL;
//         push_tok(&t, WORD, "ls");
//         push_tok(&t, PIPE, NULL);
//         run_case("ls |", t);
//     }

//     // 6) リダイレクトのオペランド欠落: echo >
//     {
//         t_token_list *t=NULL;
//         push_tok(&t, WORD, "echo");
//         push_tok(&t, OUTPUT, NULL);
//         run_case("echo >", t);
//     }

//     return 0;
// }
