#include <stdio.h>

int main(){
	char f[10000]; //the first lattice term
	char g[10000]; // the second lattice term
	//Variable Declarations: You declare character arrays f and g to hold the two lattice terms, each with a capacity of 10,000 characters. This ensures you can handle large terms.
	FILE* input; //to use a file
	FILE* output; //to create a file
	input = fopen ("Lat_id_input.txt","r+"); //to open the input file
	output = fopen ("Lat_id_output.txt","w+"); // to create an output file
//scanning..................................................................................................................................................................
	int end=0;
	int i=0;
	int flength; //the length of f
	int glength; //the length of g
	//reading the first term:........
	while(end < 1){
		fscanf (input, "%c", &f[i]);
		if(f[i] == '\n'){ // the first term ends at the first new line
			end++;
		}
		i++;
	}
	flength=i-1;//what it does here, it reads the first term and name it by f, where the first term will stop at a new line. SAME THING FOR g BELOW
	i=0;
	while(end < 2){
		fscanf (input, "%c", &g[i]); //reading the second term
		if(g[i] == '\n'){ // the second term ends at a new line
			end++;
		}
		i++;
	}
	glength=i-1;

	printf("I scanned the terms.\n"); //when the scan is done it outputs this
//length......................................................................................................................................................................
	//After scanning the terms and defining them, we want it to calculate the two terms lengths. to this, we want the program to ignore spaces and write the missing *
	//deleting empty charachters (spaces)
	for(int j=0;j < flength; j++){
		while(f[j] == ' '){
			for (int k=j;k < flength;k++){
				f[k]=f[k+1];
			}
			flength--;
		}
	}
		for(int j=0;j < glength;j++){
		while(g[j] == ' '){
			for (int k=j;k < glength;k++){
				g[k]=g[k+1];
			}
			glength--;
		}
	}

//Inserting missing '*' characters...................................................................................................................................
	for(int i=0;i < flength-1;i++){ //CASE I: after closing parantheses (if there is no + or * then it should be *)
		if(f[i] == ')'){
			if((f[i+1] != '+') && (f[i+1] != '*') && (f[i+1] != ')')){
				for(int j=flength+1;j > i+1;j--){
					f[j]=f[j-1];
				}
				f[i+1]='*';
				flength++;//update the length if f
			}
		}
	}

	for(int i=0;i < flength-1;i++){ //CASE II: After an opening parantheses (if there is no + or * then it should be *)
		if(f[i+1] == '('){
			if((f[i] != '+') && (f[i] != '*') && (f[i] != '(')){
				for(int j=flength+1;j > i+1;j--){
					f[j]=f[j-1];
				}
				f[i+1]='*';
				flength++;//update the length if f
			}
		}
	}

	for(int i=0;i < glength-1;i++){
		if(g[i] == ')'){
			if((g[i+1] != '+') && (g[i+1] != '*') && (g[i+1] != ')')){
				for(int j=glength+1;j > i+1;j--){
					g[j]=g[j-1];
				}
				g[i+1]='*';
				glength++;//update the length if g
			}
		}
	}

	for(int i=0;i < glength-1;i++){
		if(g[i+1] == '('){
			if((g[i] != '+') && (g[i] != '*') && (g[i] != '(')){
				for(int j=glength+1;j > i+1;j--){
					g[j]=g[j-1];
				}
				g[i+1]='*';
				glength++;//update the length if g
			}
		}
	}


	fprintf (output, "f has length %d, g has length: %d\n", flength, glength); //HERE THE CALCULATIONS OF THE TERMS LENGTHS ENDS
// Describing subterms.......................................................................................................................................................................
	//describing subterms of f (beginning char., ending char., type (join=1, meet=0; var.=2), height?)???
	int ftermb[2*flength]; //beginning char
	int fterme[2*flength]; //ending char
	int ftermt[2*flength]; //type (join=1, meet=0; var.=2)
	int ftermh[2*flength]; //height

	//describing subterms of g (beginning char., ending char., type (join=1, meet=0; var.=2), height)
	int gtermb[2*glength];
	int gterme[2*glength];
	int gtermt[2*glength];
	int gtermh[2*glength];

	//where we are at identifying subterms

	int fcounter=0; //tracking subterms
	int gcounter=0;
	int ffinish=0; //tracking the completion of term identification
	int gfinish=0;

//variables of f.............................................................................................................................................................
	for(int k=0;k < flength; k++){
		if(f[k] != '(' && f[k] != ')' && f[k] != '+' && f[k] != '*' && ((k == 0) || ((k > 0) && (f[k-1] == '(' || f[k-1] == ')' || f[k-1] == '+' || f[k-1] == '*')))){
                //For each character in f, if it's not (, ), +, or * and is either the first character or follows one of (,),+,*, then it's identified as a variable.
                //The start index of the variable is stored in ftermb
                //The type is set to 2
                //The height is set to 0.
                //The end index of the variable is initially set to the end of f but adjusted if another special character is found.

			ftermb[fcounter]=k;
			ftermt[fcounter]=2;
			ftermh[fcounter]=0;
			fterme[fcounter]=flength-1;
			for (int m=flength-1;m > k;m--){
				if(f[m] == '(' || f[m] == ')' || f[m] == '+' || f[m] == '*'){
					fterme[fcounter]=m-1;
				}
			}
			fprintf (output, "The %dth variable of f is ", fcounter);
			for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
				fprintf (output, "%c",f[r]);//
			}
			fprintf (output, ".\n");
			fcounter++;
		}
	}

	for(int a=0;a < fcounter; a++){
		//printf("The %dth variable of f begins at %d and ends at %d.\n",a,ftermb[a],fterme[a]);
	}

	int fvar=fcounter; //fvar keeps track of the total number of variables identified in f



	//levels of f?

	if(fcounter < 2){
		ffinish=1;//If there are fewer than two subterms (indicated by fcounter < 2), no additional joins are possible. The flag ffinish is set to 1, indicating that no further levels of joins are needed.
	}
    //for the next part: The flevel variable represents the current nesting level being evaluated for joins in f
    //The while loop runs until ffinish remains 1 for an entire iteration, indicating that no new join subterms were added at this level.
    //Each loop iteration evaluates a potential join at level flevel
	int flevel=1;
//reached here.............................................................................................................................................................................

	while (ffinish == 0){
		ffinish=1;
		//is it true that there is a join subterm of level flevel beginning at character k?
		for(int k=0;k < flength; k++){
			int c=k; //current position
			int u=-1; //position of a join term
			int d=0;  //Flag for indicating certain conditions, initially 0 (purpose is to be clarified).
			int jumps=0; //number of nesting levels
			while(c < flength){
				//printf("flength=%d, fcounter=%d, k=%d, jumps=%d and c=%d.\n",flength,fcounter,k,jumps,c);
				//if there is a term starting, but not ending earlier, then NO
				for(int h=0;h < fcounter; h++){
					if((ftermb[h] < c) && (fterme[h] >= c)){
						d=1;
					}
				}//This loop checks if any existing subterms begin before c and end after c. If so, d is set to 1, indicating that c is within another subterm, meaning a join cannot start here.

				//if a join term starts at k, then NO
				for(int h=0;h < fcounter; h++){
					if((ftermb[h] == k) && (ftermt[h] == 1)){
						d=1;
					}
				}//checks if a join subterm already begins at k. If so, it sets d = 1, indicating k is already part of an existing join.

				//the character before a join term cannot be '*'
				if((k > 0) && (f[k-1] == '*')){
					d=1;
				}


				if(d == 0){
					for(int h=0;h < fcounter; h++){
						if(ftermb[h] == c){
							if(fterme[h] > u){
								u=fterme[h];
							}
						}//This loop sets u to the end of the longest subterm starting at c, indicating the maximum range for this potential join.
					}//If d=0 then we can start a new join subterm
					if(u == flength-1){
						if(jumps > 0){
							ftermb[fcounter]=k;
							fterme[fcounter]=flength-1;
							ftermt[fcounter]=1;
							ftermh[fcounter]=flevel;
							//If u reaches the end of f (flength - 1), a complete join term is identified.
                            //The join’s start and end positions are stored in ftermb and fterme respectively, ftermt[fcounter] is set to 1 (indicating a join), and its height level
                            //ftermh[fcounter] is set to flevel.
							fprintf (output, "%dth ST of f is ", fcounter);
							for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
								fprintf (output, "%c",f[r]);
							}
							fprintf (output, ".\n");
							fcounter++;
							ffinish=0;
						}//fcounter increments, indicating a new subterm was found, and ffinish is set to 0, indicating that further levels should be evaluated.
						c=flength;
					} else if(u > -1){//This part checks if u does not reach the end but is part of a valid parenthesized expression.
                                      //Conditions verify that k and u follow parentheses rules, without forbidden operators around them.
                                      //If a valid join term is identified, it is stored similarly to the previous condition.
						if(f[u+1] == ')'){
							if((k > 0) && (f[k-1] == '(')){
								if((u > flength-3) || (f[u+2] != '+') || ((k > 1) && (f[k-2] == '*'))){
									if(jumps > 0){
										ftermb[fcounter]=k;
										fterme[fcounter]=u;
										ftermt[fcounter]=1;
										ftermh[fcounter]=flevel;
										fprintf (output, "The %dth Subterm of f is ", fcounter);
										for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
											fprintf (output, "%c",f[r]);
										}
										fprintf (output, ".\n");
										fcounter++;
										ffinish=0;
									}
									c=flength;
								} else {
									c=u+3;
									jumps++;
								}
							} else {
								c=flength;
							}
						}
						if(f[u+1] == '+'){
							c=u+2;
							jumps++;
						}
						if(f[u+1] == '*'){
							c=flength;
						}
					} else {
						if(f[c] == '('){
							for(int h=0;h < fcounter; h++){
								if(ftermb[h] == c+1){
									if(fterme[h] > u){
										u=fterme[h];
									}
								}
							}
							if((u < flength-1) && (f[u+1] == ')')){
								if(u == flength-2){
									if(jumps > 0){
										ftermb[fcounter]=k;
										fterme[fcounter]=flength-1;
										ftermt[fcounter]=1;
										ftermh[fcounter]=flevel;
										fprintf (output, "The %dth subterm of f is ", fcounter);
										for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
											fprintf (output, "%c",f[r]);
										}
										fprintf (output, ".\n");
										fcounter++;
										ffinish=0;
									}
									c=flength;
								} else {
									if(f[u+2] == ')'){
										if((k > 0) && (f[k-1] == '(')){
											if((u > flength-4) || (f[u+3] != '+')){
												if(jumps > 0){
													ftermb[fcounter]=k;
													fterme[fcounter]=u+1;
													ftermt[fcounter]=1;
													ftermh[fcounter]=flevel;
													fprintf (output, "The %dth subterm of f is ", fcounter);
													for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
														fprintf (output, "%c",f[r]);
													}
													fprintf (output, ".\n");
													fcounter++;
													ffinish=0;
												}
												c=flength;
											} else {
												c=u+4;
												jumps++;
											}
										} else {
											c=flength;
										}
									} else if(f[u+2] == '+'){
										c=u+3;
										jumps++;
									} else {
										c=flength;
									}
								}
							} else {
								c=flength;
							}
						} else {
							c=flength;
						}
					}
				} else {
					c=flength;
				}
				u=-1;
			}
		}

		//WILL DO THE SAME FOR MEETS
		//is it true that there is a meet subterm of level flevel beginning at character k?
		for(int k=0;k < flength; k++){
			int c=k;
			int u=-1;
			int d=0;
			int jumps=0;
			while(c < flength){
				printf("fcounter=%d, k=%d, d=%d and c=%d.\n",fcounter,k,d,c);
				//if there is a term starting, but not ending earlier, then NO
				for(int h=0;h < fcounter; h++){
					if((ftermb[h] < c) && (fterme[h] >= c)){
						d=1;
					}
				}
				//if a meet term starts at k, then again NO
				for(int h=0;h < fcounter; h++){
					if((ftermb[h] == k) && (ftermt[h] == 0)){
						d=1;
					}
				}
				if(d == 0){
					for(int h=0;h < fcounter; h++){
						if(ftermb[h] == c){
							if((fterme[h] > u) && (ftermh[h] < flevel)){
								u=fterme[h];
							}
						}
					}
					if(u == flength-1){
						if(jumps > 0){
							ftermb[fcounter]=k;
							fterme[fcounter]=flength-1;
							ftermt[fcounter]=0;
							ftermh[fcounter]=flevel;
							fprintf (output, "The %dth subterm of f is ", fcounter);
							for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
								fprintf (output, "%c",f[r]);
							}
							fprintf (output, ".\n");
							fcounter++;
							ffinish=0;
						}
						c=flength;
					} else if(u > -1){
						if(f[u+1] == ')'){
							if((k > 0) && (f[k-1] == '(')){
								if((u > flength-3) || (f[u+2] != '*')){
									if(jumps > 0){
										ftermb[fcounter]=k;
										fterme[fcounter]=u;
										ftermt[fcounter]=0;
										ftermh[fcounter]=flevel;
										fprintf (output, "The %dth subterm of f is ", fcounter);
										for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
											fprintf (output, "%c",f[r]);
										}
										fprintf (output, ".\n");
										fcounter++;
										ffinish=0;
									}
									c=flength;
								} else {
									c=u+3;
									jumps++;
								}
							} else if((k > 0) && (f[k-1] == '+')){
								if(jumps > 0){
									ftermb[fcounter]=k;
									fterme[fcounter]=u;
									ftermt[fcounter]=0;
									ftermh[fcounter]=flevel;
									fprintf (output, "The %dth subterm of f is ", fcounter);
									for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
										fprintf (output, "%c",f[r]);
									}
									fprintf (output, ".\n");
									fcounter++;
									ffinish=0;
								} else {
									c=flength;
								}
							} else {
								c=flength;
							}
						}
						if(f[u+1] == '*'){
							c=u+2;
							jumps++;
						}
						if(f[u+1] == '+'){
							int m=0;
							for (int h=0;h < fcounter; h++){
								if((ftermb[h] == k) && (fterme[h] == u)){
									m=1;
								}
							}
							if(m == 0){
								ftermb[fcounter]=k;
								fterme[fcounter]=u;
								ftermt[fcounter]=0;
								ftermh[fcounter]=flevel;
								fprintf (output, "The %dth subterm of f is ", fcounter);
								for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
									fprintf (output, "%c",f[r]);
								}
								fprintf (output, ".\n");
								fcounter++;
								ffinish=0;
							}
							c=flength;
						}
					} else {
						if(f[c] == '('){
							for(int h=0;h < fcounter; h++){
								if(ftermb[h] == c+1){
									if((fterme[h] > u) && (ftermh[h] < flevel)){
										u=fterme[h];
									}
								}
							}
							if((u < flength-1) && (f[u+1] == ')')){
								if(u == flength-2){
									if(jumps > 0){
										ftermb[fcounter]=k;
										fterme[fcounter]=flength-1;
										ftermt[fcounter]=0;
										ftermh[fcounter]=flevel;
										fprintf (output, "The %dth subterm of f is ", fcounter);
										for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
											fprintf (output, "%c",f[r]);
										}
										fprintf (output, ".\n");
										fcounter++;
										ffinish=0;
									}
									c=flength;
								} else {
									if(f[u+2] == '*'){
										c=u+3;
										jumps++;
									} else {
										if(jumps > 0){
											ftermb[fcounter]=k;
											fterme[fcounter]=u+1;
											ftermt[fcounter]=0;
											ftermh[fcounter]=flevel;
											fprintf (output, "The %dth subterm of f is ", fcounter);
											for(int r=ftermb[fcounter];r <= fterme[fcounter];r++){
												fprintf (output, "%c",f[r]);
											}
											fprintf (output, ".\n");
											fcounter++;
											ffinish=0;
										}
										c=flength;
									}
								}
							} else {
								c=flength;
							}
						} else {
							c=flength;
						}
					}
				} else {
					c=flength;
				}
				u=-1;
			}
		}
		flevel++;
		//printf("I am done by subterms of level %d of f, so far there are %d subterms.\n",flevel-1,fcounter);
		for (int h=0;h < flength;h++){
			if(ftermb[h] == 0){
				if(fterme[h] == flength-1){
					ffinish=1;
				}
			}
		}
		if(flevel > flength){
			ffinish=1;
		}
	}




	//WILL DO EVERYTHING AGAIN FOR g
	//variables of g
	for(int k=0;k < glength; k++){
		if(g[k] != '(' && g[k] != ')' && g[k] != '+' && g[k] != '*' && ((k == 0) || ((k > 0) && (g[k-1] == '(' || g[k-1] == ')' || g[k-1] == '+' || g[k-1] == '*')))){
			gtermb[gcounter]=k;
			gtermt[gcounter]=2;
			gtermh[gcounter]=0;
			gterme[gcounter]=glength-1;
			for (int m=glength-1;m > k;m--){
				if(g[m] == '(' || g[m] == ')' || g[m] == '+' || g[m] == '*'){
					gterme[gcounter]=m-1;
				}
			}
			fprintf (output, "The %dth variable of g is ", gcounter);
			for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
				fprintf (output, "%c",g[r]);
			}
			fprintf (output, ".\n");
			gcounter++;
		}
	}

	int gvar=gcounter;



	//levels of g

	if(gcounter < 2){
		gfinish=1;
	}

	int glevel=1;

	while (gfinish == 0){
		gfinish=1;
		//is it true that there is a join subterm of level glevel beginning at character k?
		for(int k=0;k < glength; k++){
			int c=k;
			int u=-1;
			int d=0;
			int jumps=0;
			while(c < glength){
				printf("glength=%d, gcounter=%d, k=%d and c=%d.\n",glength,gcounter,k,c);
				//if there is a term starting, but not ending earlier, then NO
				for(int h=0;h < gcounter; h++){
					if((gtermb[h] < c) && (gterme[h] >= c)){
						d=1;
					}
				}
				//if a join term starts at k, then again NO
				for(int h=0;h < gcounter; h++){
					if((gtermb[h] == k) && (gtermt[h] == 1)){
						d=1;
					}
				}
				//the character before a join term cannot be '*'
				if((k > 0) && (g[k-1] == '*')){
					d=1;
				}
				if(d == 0){
					for(int h=0;h < gcounter; h++){
						if(gtermb[h] == c){
							if(gterme[h] > u){
								u=gterme[h];
							}
						}
					}
					if(u == glength-1){
						if(jumps > 0){
							gtermb[gcounter]=k;
							gterme[gcounter]=glength-1;
							gtermt[gcounter]=1;
							gtermh[gcounter]=glevel;
							fprintf (output, "The %dth subterm of g is ", gcounter);
							for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
								fprintf (output, "%c",g[r]);
							}
							fprintf (output, ".\n");
							gcounter++;
							gfinish=0;
						}
						c=glength;
					} else if(u > -1){
						if(g[u+1] == ')'){
							if((k > 0) && (g[k-1] == '(')){
								if((u > glength-3) || (g[u+2] != '+') || ((k > 1) && (g[k-2] == '*'))){
									if(jumps > 0){
										gtermb[gcounter]=k;
										gterme[gcounter]=u;
										gtermt[gcounter]=1;
										gtermh[gcounter]=glevel;
										fprintf (output, "The %dth subterm of g is ", gcounter);
										for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
											fprintf (output, "%c",g[r]);
										}
										fprintf (output, ".\n");
										gcounter++;
										gfinish=0;
									}
									c=glength;
								} else {
									c=u+3;
									jumps++;
								}
							} else {
								c=glength;
							}
						}
						if(g[u+1] == '+'){
							c=u+2;
							jumps++;
						}
						if(g[u+1] == '*'){
							c=glength;
						}
					} else {
						if(g[c] == '('){
							for(int h=0;h < gcounter; h++){
								if(gtermb[h] == c+1){
									if(gterme[h] > u){
										u=gterme[h];
									}
								}
							}
							if((u < glength-1) && (g[u+1] == ')')){
								if(u == glength-2){
									if(jumps > 0){
										gtermb[gcounter]=k;
										gterme[gcounter]=glength-1;
										gtermt[gcounter]=1;
										gtermh[gcounter]=glevel;
										fprintf (output, "The %dth subterm of g is ", gcounter);
										for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
											fprintf (output, "%c",g[r]);
										}
										fprintf (output, ".\n");
										gcounter++;
										gfinish=0;
									}
									c=glength;
								} else {
									if(g[u+2] == ')'){
										if((k > 0) && (g[k-1] == '(')){
											if((u > glength-4) || (g[u+3] != '+')){
												if(jumps > 0){
													gtermb[gcounter]=k;
													gterme[gcounter]=u+1;
													gtermt[gcounter]=1;
													gtermh[gcounter]=glevel;
													fprintf (output, "The %dth subterm of g is ", gcounter);
													for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
														fprintf (output, "%c",g[r]);
													}
													fprintf (output, ".\n");
													gcounter++;
													gfinish=0;
												}
												c=glength;
											} else {
												c=u+4;
												jumps++;
											}
										} else {
											c=glength;
										}
									} else if(g[u+2] == '+'){
										c=u+3;
										jumps++;
									} else {
										c=glength;
									}
								}
							} else {
								c=glength;
							}
						} else {
							c=glength;
						}
					}
				} else {
					c=glength;
				}
				u=-1;
			}
		}
		//is it true that there is a meet subterm of level glevel beginning at character k?
		for(int k=0;k < glength; k++){
			int c=k;
			int u=-1;
			int d=0;
			int jumps=0;
			while(c < glength){
				//printf("gcounter=%d, k=%d and c=%d.\n",gcounter,k,c);
				//if there is a term starting, but not ending earlier, then NO
				for(int h=0;h < gcounter; h++){
					if((gtermb[h] < c) && (gterme[h] >= c)){
						d=1;
					}
				}
				//if a meet term starts at k, then again NO
				for(int h=0;h < gcounter; h++){
					if((gtermb[h] == k) && (gtermt[h] == 0)){
						d=1;
					}
				}
				if(d == 0){
					for(int h=0;h < gcounter; h++){
						if(gtermb[h] == c){
							if((gterme[h] > u) && (gtermh[h] < glevel)){
								u=gterme[h];
							}
						}
					}
					if(u == glength-1){
						if(jumps > 0){
							gtermb[gcounter]=k;
							gterme[gcounter]=glength-1;
							gtermt[gcounter]=0;
							gtermh[gcounter]=glevel;
							fprintf (output, "The %dth subterm of g is ", gcounter);
							for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
								fprintf (output, "%c",g[r]);
							}
							fprintf (output, ".\n");
							gcounter++;
							gfinish=0;
						}
						c=glength;
					} else if(u > -1){
						if(g[u+1] == ')'){
							if((k > 0) && (g[k-1] == '(')){
								if((u > glength-3) || (g[u+2] != '*')){
									if(jumps > 0){
										gtermb[gcounter]=k;
										gterme[gcounter]=u;
										gtermt[gcounter]=0;
										gtermh[gcounter]=glevel;
										fprintf (output, "The %dth subterm of g is ", gcounter);
										for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
											fprintf (output, "%c",g[r]);
										}
										fprintf (output, ".\n");
										gcounter++;
										gfinish=0;
									}
									c=glength;
								} else {
									c=u+3;
									jumps++;
								}
							} else if((k > 0) && (g[k-1] == '+')){
								if(jumps > 0){
									gtermb[gcounter]=k;
									gterme[gcounter]=u;
									gtermt[gcounter]=0;
									gtermh[gcounter]=glevel;
									fprintf (output, "The %dth subterm of g is ", gcounter);
									for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
										fprintf (output, "%c",g[r]);
									}
									fprintf (output, ".\n");
									gcounter++;
									gfinish=0;
								} else {
									c=glength;
								}
							} else {
								c=glength;
							}
						}
						if(g[u+1] == '*'){
							c=u+2;
							jumps++;
						}
						if(g[u+1] == '+'){
							int m=0;
							for (int h=0;h < gcounter; h++){
								if((gtermb[h] == k) && (gterme[h] == u)){
									m=1;
								}
							}
							if(m == 0){
								gtermb[gcounter]=k;
								gterme[gcounter]=u;
								gtermt[gcounter]=0;
								gtermh[gcounter]=glevel;
								fprintf (output, "The %dth subterm of g is ", gcounter);
								for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
									fprintf (output, "%c",g[r]);
								}
								fprintf (output, ".\n");
								gcounter++;
								gfinish=0;
							}
							c=glength;
						}
					} else {
						if(g[c] == '('){
							for(int h=0;h < gcounter; h++){
								if(gtermb[h] == c+1){
									if((gterme[h] > u) && (gtermh[h] < glevel)){
										u=gterme[h];
									}
								}
							}
							if((u < glength-1) && (g[u+1] == ')')){
								if(u == glength-2){
									if(jumps > 0){
										gtermb[gcounter]=k;
										gterme[gcounter]=glength-1;
										gtermt[gcounter]=0;
										gtermh[gcounter]=glevel;
										fprintf (output, "The %dth subterm of g is ", gcounter);
										for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
											fprintf (output, "%c",g[r]);
										}
										fprintf (output, ".\n");
										gcounter++;
										gfinish=0;
									}
									c=glength;
								} else {
									if(g[u+2] == '*'){
										c=u+3;
										jumps++;
									} else {
										if(jumps > 0){
											gtermb[gcounter]=k;
											gterme[gcounter]=u+1;
											gtermt[gcounter]=0;
											gtermh[gcounter]=glevel;
											fprintf (output, "The %dth subterm of g is ", gcounter);
											for(int r=gtermb[gcounter];r <= gterme[gcounter];r++){
												fprintf (output, "%c",g[r]);
											}
											fprintf (output, ".\n");
											gcounter++;
											gfinish=0;
										}
										c=glength;
									}
								}
							} else {
								c=glength;
							}
						} else {
							c=glength;
						}
					}
				} else {
					c=glength;
				}
				u=-1;
			}
		}
		glevel++;
		//printf("I am done by subterms of level %d of g, so far there are %d subterms.\n",glevel-1,gcounter);
		for (int h=0;h < glength;h++){
			if(gtermb[h] == 0){
				if(gterme[h] == glength-1){
					gfinish=1;
				}
			}
		}
		if(glevel > glength){
			gfinish=1;
		}
	}


	//Calculating depth from height???

	int ftermd[fcounter];
	for (int i=0;i < fcounter;i++){
		ftermd[i]=ftermh[fcounter-1];
	}
	int fdepthfinish=0;
	while(fdepthfinish == 0){
		fdepthfinish=1;
		for(int i=0;i < fcounter;i++){
			for(int j=0;j < fcounter;j++){
				if((ftermb[i] <= ftermb[j]) && (fterme[i] >= fterme[j])){
					if((ftermb[i] != ftermb[j]) || (fterme[i] != fterme[j])){
						if(ftermd[i] == ftermd[j]){
							ftermd[j]=ftermd[i]-1;
							fdepthfinish=0;
						}
					}
				}
			}
		}
	}

	int gtermd[gcounter];
	for (int i=0;i < gcounter;i++){
		gtermd[i]=gtermh[gcounter-1];
	}
	int gdepthfinish=0;
	while(gdepthfinish == 0){
		gdepthfinish=1;
		for(int i=0;i < gcounter;i++){
			for(int j=0;j < gcounter;j++){
				if((gtermb[i] <= gtermb[j]) && (gterme[i] >= gterme[j])){
					if((gtermb[i] != gtermb[j]) || (gterme[i] != gterme[j])){
						if(gtermd[i] == gtermd[j]){
							gtermd[j]=gtermd[i]-1;
							gdepthfinish=0;
						}
					}
				}
			}
		}
	}

	//Here starts the main part of the program.
	int se[flength+glength][flength+glength];
	int ge[flength+glength][flength+glength];

	//The initial values should be constant 0, but better be sure.

	for(int i=0;i < flength+glength;i++){
		for(int j=0;j < flength+glength;j++){
			se[i][j]=0;
			ge[i][j]=0;
		}
	}

	//Which variables are the same?

	for (int i=0;i < fvar;i++){
		for (int j=0;j < fvar;j++){
			if(fterme[i] - ftermb[i] == fterme[j] - ftermb[j]){
				se[i][j]=1;
				for(int s=0;s < fterme[i]-ftermb[i]+1;s++){
					if(f[ftermb[i]+s] != f[ftermb[j]+s]){
						se[i][j]=0;
					}
				}
			}
		}
	}
	for (int i=0;i < fvar;i++){
		for (int j=0;j < gvar;j++){
			if(fterme[i] - ftermb[i] == gterme[j] - gtermb[j]){
				se[i][fcounter+j]=1;
				for(int s=0;s < fterme[i]-ftermb[i]+1;s++){
					if(f[ftermb[i]+s] != g[gtermb[j]+s]){
						se[i][fcounter+j]=0;
					}
				}
			}
		}
	}
	for (int i=0;i < gvar;i++){
		for (int j=0;j < fvar;j++){
			if(gterme[i] - gtermb[i] == fterme[j] - ftermb[j]){
				se[fcounter+i][j]=1;
				for(int s=0;s < gterme[i]-gtermb[i]+1;s++){
					if(g[gtermb[i]+s] != f[ftermb[j]+s]){
						se[fcounter+i][j]=0;
					}
				}
			}
		}
	}
	for (int i=0;i < gvar;i++){
		for (int j=0;j < gvar;j++){
			if(gterme[i] - gtermb[i] == gterme[j] - gtermb[j]){
				se[fcounter+i][fcounter+j]=1;
				for(int s=0;s < gterme[i]-gtermb[i]+1;s++){
					if(g[gtermb[i]+s] != g[gtermb[j]+s]){
						se[fcounter+i][fcounter+j]=0;
					}
				}
			}
		}
	}

	//Which terms are smaller or equal than which in the free lattice?

	int finish=0;

	while(finish == 0){
		finish=1;
		for(int i=0;i < fcounter+gcounter;i++){
			for(int j=0;j < fcounter+gcounter;j++){
				if((se[i][j] == 0) && (ge[j][i] == 1)){
					se[i][j]=1;
					finish=0;
				}
				if((se[i][j] == 1) && (ge[j][i] == 0)){
					ge[j][i]=1;
					finish=0;
				}
			}
		}

		for(int i=0;i < fcounter;i++){
			for(int j=0;j < fcounter+gcounter;j++){
				if(ftermt[i] == 0){
					for(int h=0;h < fcounter;h++){
						if((ftermb[h] >= ftermb[i]) && (fterme[h] <= fterme[i])){
							if(ftermd[h] == ftermd[i]-1){
								if(se[h][j] == 1){
									if(se[i][j] == 0){
										se[i][j]=1;
										finish=0;
									}
								}
							}
						}
					}
					int p=1;
					for(int h=0;h < fcounter;h++){
						if((ftermb[h] >= ftermb[i]) && (fterme[h] <= fterme[i])){
							if(ftermd[h] == ftermd[i]-1){
								if(ge[h][j] == 0){
									p=0;
								}
							}
						}
					}
					if((p == 1) && (ge[i][j] == 0)){
						ge[i][j]=1;
						finish=0;
					}
				}
				if(ftermt[i] == 1){
					for(int h=0;h < fcounter;h++){
						if((ftermb[h] >= ftermb[i]) && (fterme[h] <= fterme[i])){
							if(ftermd[h] == ftermd[i]-1){
								if(ge[h][j] == 1){
									if(ge[i][j] == 0){
										ge[i][j]=1;
										finish=0;
									}
								}
							}
						}
					}
					int p=1;
					for(int h=0;h < fcounter;h++){
						if((ftermb[h] >= ftermb[i]) && (fterme[h] <= fterme[i])){
							if(ftermd[h] == ftermd[i]-1){
								if(se[h][j] == 0){
									p=0;
								}
							}
						}
					}
					if((p == 1) && (se[i][j] == 0)){
						se[i][j]=1;
						finish=0;
					}
				}
			}
		}

		for(int i=0;i < gcounter;i++){
			for(int j=0;j < fcounter+gcounter;j++){
				if(gtermt[i] == 0){
					for(int h=0;h < gcounter;h++){
						if((gtermb[h] >= gtermb[i]) && (gterme[h] <= gterme[i])){
							if(gtermd[h] == gtermd[i]-1){
								if(se[fcounter+h][j] == 1){
									if(se[fcounter+i][j] == 0){
										se[fcounter+i][j]=1;
										finish=0;
									}
								}
							}
						}
					}
					int p=1;
					for(int h=0;h < gcounter;h++){
						if((gtermb[h] >= gtermb[i]) && (gterme[h] <= gterme[i])){
							if(gtermd[h] == gtermd[i]-1){
								if(ge[fcounter+h][j] == 0){
									p=0;
								}
							}
						}
					}
					if((p == 1) && (ge[fcounter+i][j] == 0)){
						ge[fcounter+i][j]=1;
						finish=0;
					}
				}
				if(gtermt[i] == 1){
					for(int h=0;h < gcounter;h++){
						if((gtermb[h] >= gtermb[i]) && (gterme[h] <= gterme[i])){
							if(gtermd[h] == gtermd[i]-1){
								if(ge[fcounter+h][j] == 1){
									if(ge[fcounter+i][j] == 0){
										ge[fcounter+i][j]=1;
										finish=0;
									}
								}
							}
						}
					}
					int p=1;
					for(int h=0;h < gcounter;h++){
						if((gtermb[h] >= gtermb[i]) && (gterme[h] <= gterme[i])){
							if(gtermd[h] == gtermd[i]-1){
								if(se[fcounter+h][j] == 0){
									p=0;
								}
							}
						}
					}
					if((p == 1) && (se[fcounter+i][j] == 0)){
						se[fcounter+i][j]=1;
						finish=0;
					}
				}
			}
		}
	}


	for(int i=0;i<fcounter+gcounter;i++){
		for(int j=0;j<fcounter+gcounter;j++){
			fprintf (output, "%d\t",se[i][j]);
		}
		fprintf (output, "\n");
	}
	if(se[fcounter-1][fcounter+gcounter-1] == 0){
		fprintf (output, "f<=g is not true in the free lattice.\n");
	} else {
		fprintf (output, "f<=g is true in the free lattice. because \n", se[fcounter-1][fcounter+gcounter-1] );
	}

	fclose(input);
	fclose(output);
	return 0;
}

