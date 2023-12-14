// Universidad Rafael Urdaneta. José Carrillo. C.I. 30739823. Evaluación #3 de Sistemas Operativos

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int longitud, lext, cf, cl, crr, f, Q, noop, //longitud extendible, clocks de FIFO, LIFO y RR, flag, Quantum y acumulador de noop
ti[40], til[40], tif[40], t[40], tirr[40], trr[40], atrr, //Arrays enteros de entrada

tffifo[40],TF[40], EF[40],
tflifo[40], TL[40], EL[40], //Arrays enteros de salida/respuesta
tfrr[40], TRR[40], ERR[40];

float IF[40], IL[40], IRR[40], //Arrays de I, decimales
pTF, pEF, pIF, pTL, pEL, pIL, pTRR, pERR, pIRR; //Promedios

clock_t start, end; // Inicio y Final del Contador de Tiempo
double timef, timel, timerr; //Tiempos de cálculo de cada proceso

void Input();
void Mostrar();

int main(){
	
		Input();
		
		// Proceso de FIFO
		
		start = clock();
		cf = 0;
		
		for (int i = 0; i<lext; i++){
			
			f = 0;
			
			for (int j = 0; f != 1; j++){
			
				if (j == longitud){
					
					cf++;
					lext++;
					noop++;
					f = 1;	
				}else if (tif[j]<=cf){
				
					tffifo[j] = t[j] + cf;
					cf = tffifo[j];	
					tif[j] = 9999;
					f = 1;
				}
			}	
		}
		
		cf += noop;
		
		for (int i = 0; i<longitud; i++){
		
			TF[i] = tffifo[i] - ti[i]; pTF += TF[i];
			EF[i] = TF[i] - t[i]; pEF += EF[i]; 	
			IF[i] = (float)t[i]/TF[i]; pIF += IF[i];	
		}
		
		pTF = pTF / longitud;
		pEF = pEF / longitud;
		pIF = pIF / longitud;
		
		end = clock();
		timef = (double)(end - start)/CLOCKS_PER_SEC;
				
		//Proceso de LIFO		
				
		start = clock();		
		cl = 0;
		lext = longitud;
		noop = 0;
		
		for (int i = 0; i<lext; i++){
			
			f = 0;	
			
			for (int j = longitud-1; f != 1; j--){
				
				if (j < 0){
					
					cl++;
					lext++;
					noop++;
					f = 1;	
				}else if (til[j]<=cl){
				
					tflifo[j] = t[j] + cl;
					cl = tflifo[j];	
					til[j] = 9999;
					f = 1;
				}
			}	
		}
		
		cl += noop;
		
		for (int i = 0; i<longitud; i++){
		
			TL[i] = tflifo[i] - ti[i]; pTL += TL[i];	
			EL[i] = TL[i] - t[i]; pEL += EL[i];		
			IL[i] = (float)t[i]/TL[i]; pIL += IL[i];
		}

		pTL = pTL / longitud;
		pEL = pEL / longitud;
		pIL = pIL / longitud;
		
		end = clock();
		timel = (double)(end - start)/CLOCKS_PER_SEC;
		
		//Proceso de Round Robin
		
		start = clock();
		crr = 0;
		noop = 0;
		
		for (int i = 0; i<longitud; i++){
			atrr+= trr[i];
		}
		
		for (int i = 0; atrr > 0; i++){
		
			f = 0;	
			
			for (int j = 0; j<longitud; j++){
				
				 if (tirr[j]<=crr){
					
					if (trr[j]<=Q){
						
						tfrr[j] = trr[j] + crr;
						crr = tfrr[j];
						tirr[j] = 9999;
						atrr = atrr - trr[j];
						f++;
					}else{
					
						trr[j] = trr[j] - Q;
						atrr -= Q;
						crr += Q;
						f++;						
					}	
				}
			}
			if (f == 0){
				crr++;
				noop++;
			} 		
		}
		
		crr += noop;
		
		for (int i = 0; i<longitud; i++){
		
			TRR[i] = tfrr[i] - ti[i]; pTRR += TRR[i];	
			ERR[i] = TRR[i] - t[i]; pERR += ERR[i];		
			IRR[i] = (float)t[i]/TRR[i]; pIRR += IRR[i];
		}

		pTRR = pTRR / longitud;
		pERR = pERR / longitud;
		pIRR = pIRR / longitud;

		end = clock();
		timerr = (double)(end - start)/CLOCKS_PER_SEC;
		  
		Mostrar();
		  
		return 0;	
	}
    
    
void Mostrar(){
	
		//FIFO
		printf ("\n\t1. FIFO\n\n\tP.\tti\tt\ttf\tT \tE \t I \n\n");
		
		for (int i = 0; i<longitud; i++){
			
			if (i<26){
			
				printf ("\t%c\t%d\t%d\t%d\t%d\t%d\t%.3f", i+65, ti[i], t[i], tffifo[i], TF[i], EF[i], IF[i]);
				printf ("\n");
			}else{
				printf ("\t%c%d\t%d\t%d\t%d\t%d\t%d\t%.3f", i+39, 1, ti[i], t[i], tffifo[i], TF[i], EF[i], IF[i]);
				printf ("\n");
			}
		}
		
		printf ("\n\tPromedios\t\t%d\t%.3f\t%.3f\t%.3f", cf, pTF, pEF, pIF);
		printf ("\n\n\tTiempo de Calculo (Tiende a 0): %.3f s.", timef);
		
		//LIFO
		printf ("\n\n\n\t2. LIFO\n\n\tP.\tti\tt\ttf\tT \tE \t I \n\n");
		
		for (int i = 0; i<longitud; i++){
			
			if (i<26){
				printf ("\t%c\t%d\t%d\t%d\t%d\t%d\t%.3f", i+65, ti[i], t[i], tflifo[i], TL[i], EL[i], IL[i]);
				printf ("\n");
			}else{
				printf ("\t%c%d\t%d\t%d\t%d\t%d\t%d\t%.3f", i+39, 1, ti[i], t[i], tflifo[i], TL[i], EL[i], IL[i]);
				printf ("\n");
			}
		}
		
		printf ("\n\tPromedios\t\t%d\t%.3f\t%.3f\t%.3f", cl, pTL, pEL, pIL);
		printf ("\n\n\tTiempo de Calculo (Tiende a 0): %.3f s.", timel);
		
		//Round Robin
		printf ("\n\n\n\t3. ROUND ROBIN\n\n\tP.\tti\tt\ttf\tT \tE \t I \n\n");
		
		for (int i = 0; i<longitud; i++){
			
			if (i<26){
				printf ("\t%c\t%d\t%d\t%d\t%d\t%d\t%.3f", i+65, ti[i], t[i], tfrr[i], TRR[i], ERR[i], IRR[i]);
				printf ("\n");	
			}else{
				printf ("\t%c%d\t%d\t%d\t%d\t%d\t%d\t%.3f", i+39, 1, ti[i], t[i], tfrr[i], TRR[i], ERR[i], IRR[i]);
				printf ("\n");
			}
		}
		
		printf ("\n\tPromedios\t\t%d\t%.3f\t%.3f\t%.3f", crr, pTRR, pERR, pIRR);
		printf ("\n\n\tTiempo de Calculo (Tiende a 0): %.3f s.\n\n", timerr);
		
		if (pTF <= pTL && pTF <= pTRR) printf ("\tFIFO fue el mas eficiente en T.\n");
		if (pTL <= pTF && pTL <= pTRR) printf ("\tLIFO fue el mas eficiente en T.\n");
		if (pTRR <= pTF && pTRR <= pTL) printf ("\tRound Robin fue el mas eficiente en T.\n");
		
		if (pEF <= pEL && pEF <= pERR) printf ("\tFIFO fue el mas eficiente en E.\n");
		if (pEL <= pEF && pEL <= pERR) printf ("\tLIFO fue el mas eficiente en E.\n");
		if (pERR <= pEF && pERR <= pEL) printf ("\tRound Robin fue el mas eficiente en E.\n");
		
		if (pIF >= pIL && pIF >= pIRR) printf ("\tFIFO fue el mas eficiente en I.\n");
		if (pIL >= pIF && pIL >= pIRR) printf ("\tLIFO fue el mas eficiente en I.\n");
		if (pIRR >= pIF && pIRR >= pIL) printf ("\tRound Robin fue el mas eficiente en I.\n");
	}     
    
    
void Input(){
	
		do{
		printf ("Introduce el numero de actividades (Menor a 40): ");
		scanf ("%d", &longitud);	
		}while (longitud>40 || longitud < 1);
				
		lext = longitud;
				
		printf ("Introduce el numero del Quantum de Round Robin: ");
		scanf ("%d", &Q);		
			
		for (int i = 0; i<longitud; i++){ 	
				
			if (i<26){
			
				printf ("\nIntroduce el tiempo de inicio de la actividad %c: ", i+65);
				scanf ("%d", &ti[i]);
			
				tif[i] = til[i] = tirr[i] = ti[i];
			
				printf ("Introduce el tiempo de la actividad %c: ", i+65);
				scanf ("%d", &t[i]);		
			
				trr[i] = t[i];
			
				}else{
				
				printf ("\nIntroduce el tiempo de inicio de la actividad %c%d: ", i+39, 1);
				scanf ("%d", &ti[i]);
			
				tif[i] = til[i] = tirr[i] = ti[i];
			
				printf ("Introduce el tiempo de la actividad %c%d: ", i+39, 1);
				scanf ("%d", &t[i]);
			
				trr[i] = t[i];
			}
		}
	}

