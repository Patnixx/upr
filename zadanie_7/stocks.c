#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stock {
    int day;
    char name[20]; //riadok ma max 100 chars a 5 udajov cize 100/5 = 20
    float start;
    float end;
    float diff;
    int trades;
    char norm_trades[20];
};

void print_header(char *stock, int lines, struct Stock *line) { //header s najväčšou volume
    int is_mentioned = 0;
    int where_highest = 0;
    int index = 0;
    for(int i = 0; i < lines; i++) {
        if(strcmp(line[i].name, stock) == 0){
            is_mentioned = 1;
            if(line[i].trades > where_highest) {
                where_highest = line[i].trades;
                index = i;
            }
        }
    }
    if(is_mentioned) {
        printf("<div>\n");
        printf("<h1>%s: highest volume</h1>\n", line[index].name);
        printf("<div>Day: %d</div>\n", line[index].day);
        printf("<div>Start price: %.2f</div>\n", line[index].start);
        printf("<div>End price: %.2f</div>\n", line[index].end);
        printf("<div>Volume: %s</div>\n", line[index].norm_trades);
        printf("</div>\n");
    }
    else {
        printf("<div>\n");
        printf("Ticker AMC was not found\n");
        printf("</div>\n");
    }
}

void print_stock(struct Stock *line, int lines, char *stock) { //jednotlive stocks
    for(int i = lines-1; i >= 0; i--) {
        printf("<tr>\n");
        if(strcmp(line[i].name, stock) == 0) {
            printf("\t<td><b>%d</b></td>\n", line[i].day);
            printf("\t<td><b>%s</b></td>\n", line[i].name);
            printf("\t<td><b>%.2f</b></td>\n", line[i].start);
            printf("\t<td><b>%.2f</b></td>\n", line[i].end);
            printf("\t<td><b>%.2f</b></td>\n", line[i].diff);
            printf("\t<td><b>%s</b></td>\n", line[i].norm_trades);
            printf("</tr>\n");
        }
        else{
            printf("\t<td>%d</td>\n", line[i].day);
            printf("\t<td>%s</td>\n", line[i].name);
            printf("\t<td>%.2f</td>\n", line[i].start);
            printf("\t<td>%.2f</td>\n", line[i].end);
            printf("\t<td>%.2f</td>\n", line[i].diff);
            printf("\t<td>%s</td>\n", line[i].norm_trades);
            printf("</tr>\n");
        }
    }
}

void print_whole(char *stock, int lines, struct Stock *line) { //celok
    printf("<html>\n");
    printf("<body>\n");
    print_header(stock, lines, line);
    printf("<table>\n");
    printf("<thead>\n");
    printf("<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n");
    printf("</thead>\n");
    printf("<tbody>\n");
    print_stock(line, lines, stock);
    printf("</tbody>\n");
    printf("</table>\n");
    printf("</body>\n");
    printf("</html>\n");
}

void normalise_trades(char *token, char *trades_norm) { //vjebanie podtrzitka do pipinky
    size_t len = strlen(token);
    size_t mod = len % 3;
    if (mod == 0) mod = 3;

    size_t pos = 0;

    strncpy(trades_norm, token, mod);
    pos += mod;

    for (size_t i = mod; i < len; i += 3) {
        trades_norm[pos++] = '_';
        strncpy(&trades_norm[pos], &token[i], 3);
        pos += 3;
    }
    trades_norm[pos] = '\0';
}

int main(int argc, char *argv[]) {
    //vars
    char stock[20];
    int params = 6;
    struct Stock *line = NULL;
    char input[101];
    char trades_norm[20];

    //test 1
    if((argv[1] == NULL || argv[2] == NULL) && argc != 3) {
        printf("Wrong parameters\n");
        return 1;
    }

    strcpy(stock, argv[1]);
    int lines = atoi(argv[2]);

    struct Stock *temp = realloc(line,lines * params * sizeof(struct Stock));
    line = temp;
    
    //toto sa da dat do funkcie ale nechce sa mi to
    for(int i = 0; i < lines; i++) {
        fgets(input, sizeof(input), stdin);
        size_t len = strlen(input);
        if(len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        char *token = strtok(input, ",");
        //den
        if(!token) break;
        line[i].day = atoi(token);
        token = strtok(NULL, ",");
        //nazov
        if(!token) break;
        strcpy(line[i].name, token);
        token = strtok(NULL, ",");
        //start
        if(!token) break;
        line[i].start = strtof(token, NULL); //kelvin type shit
        token = strtok(NULL, ",");
        //end
        if(!token) break;
        line[i].end = strtof(token, NULL); //kelvin type shit
        token = strtok(NULL, ",");
        //diff
        float difference = line[i].end - line[i].start;
        line[i].diff = difference;
        //trades
        if(!token) break;
        line[i].trades = atoi(token);
        normalise_trades(token, trades_norm);
        strcpy(line[i].norm_trades, trades_norm);

        token = strtok(NULL, ",");
    }
    print_whole(stock, lines, line);
}