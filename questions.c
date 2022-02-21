/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * GROUP MEMBERS: Nathan Yohanes, Walid Ayub, Saaruca Kugarajh
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    for(int i = 0; i < NUM_QUESTIONS; i++){
        strcpy(questions[i].category, categories[i%3]);
        strcpy(questions[i].question, question_bank[i]); 
        strcpy(questions[i].answer, answer_bank[i]);
        questions[i].value = ((i/3) * 100) + 100;
        questions[i].answered = false;
    }
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    printf("------------------------------------------------\n");
    for(int i = 0; i < NUM_QUESTIONS; i++){
    	if (questions[i].answered == true){
    		int space = strlen(questions[i].category) + 6;
    		printf("%*s", space, " |");
    	}
        if (questions[i].answered == false){
        if (questions[i].value == 100){
            printf("\033[0;34m%s %d\033[0m |", questions[i].category,questions[i].value);
        }
        else if (questions[i].value == 200){
            printf("\033[0;35m%s %d\033[0m |", questions[i].category,questions[i].value);
        }
        else if (questions[i].value == 300){
            printf("\033[0;36m%s %d\033[0m |", questions[i].category,questions[i].value);
        }
        else{
            printf("\033[0;32m%s %d\033[0m |", questions[i].category,questions[i].value);
        }
        

        }
        if(questions[i].value != questions[i+1].value){
        	printf("\n------------------------------------------------\n");
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    int i = 0;
    while(i < NUM_QUESTIONS){
        if(strcmp(&questions[i].category, category) == 0 && questions[i].value == value){
            printf("--------------\n");
            printf("\033[0;36mQUESTION (%s %d):\033[0m %s\n", &questions[i].category, questions[i].value, &questions[i].question);
            printf("%s", "\033[0;33mANSWER (must include what/who is/are):\033[0m ");
        }
        i++;
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    int i = 0;

    // Look into string comparison functions
    while(i < NUM_QUESTIONS){
        if(strcmp(&questions[i].category, category) == 0 && questions[i].value == value) {
            questions[i].answered = true;
            printf("--------------\n");
            printf("ACTUAL ANSWER: %s\n", questions[i].answer);
            if (strcmp(&questions[i].answer, answer) == 0){
                return true;
            }
        }
        i++;
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    int i = 0;

    // lookup the question and see if it's already been marked as answered
    while(i < NUM_QUESTIONS){
        if(strcmp(&questions[i].category, category) == 0 && questions[i].value == value && !questions[i].answered){
            return false;
        }
        i++;
    }
    // return true if already exists after showing error
    printf("--------------\n");
    printf("%s\n", "Question unavailable. Please choose a different one.");
    sleep(1);
    return true;
}
