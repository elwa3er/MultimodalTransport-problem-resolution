#include <ilcplex/ilocplex.h>
#include<ctime>
#include<iostream>
#include<cstdlib>
ILOSTLBEGIN
int main(int, char**)
{
	IloEnv env;
	IloCplex cplex(env);
	IloModel model(env);
	model.setName("PFE Nesrine");
	try {
		//Déclaration des paramètres
		IloInt m, kk, n, d, cs, verif;
		IloNum kp, kv, ccd;
		IloInt tcd = 1440;
		IloInt64 Z;
		IloInt ts = rand() % 5 + 3;
		ts = ts * 24 * 60;
		ifstream instance("e:\instance.txt");
		//Lecture des données--------------------------------------------------------------
		//1 n,m,d
		instance >> n;
		instance >> m;
		instance >> d;
		printf("n=%d\t|m=%d\t|d=%d\t|\n", n, m, d);//test lecture n,m et d
		printf("\n");
		/**********************************************************************************/
		IloIntArray elig(env, n);//
		for (int i = 0; i < n; i++)
			instance >> elig[i];
		//test de lecture eligible
		printf("Eligible\n");
		for (int i = 0; i < n; i++)
			printf("%d\t|", elig[i]);
		printf("\n");
		/************************************************************************************/
		IloIntArray couv(env, m);
		int med4 = 0;
		int aa1 = 0;
		int i1 = 0;
		int j1 = 0;
		for (i1 = 0; i1 < n; i1++)
		{
			instance >> med4;
			if (elig[i1] != 0)
			{
				couv[aa1] = med4;
				aa1 = aa1 + 1;

			}

		}
		//test de  lecture couv
		printf("Cout ouverture\n");
		for (int i = 0; i < m; i++)
		printf("%d\t|", couv[i]);
		printf("\n");
		/*************************************************************************************/
		IloIntArray s(env, n);
		for (int i = 0; i < n; i++)
			instance >> s[i];
		//test de lecture de nb camion
		printf("Nombre de camions\n");
		for (int i = 0; i < n; i++)		
		printf("%d\t|", s[i]);
		printf("\n");

		/***************************************************************************************/
		//2 Coût de transport à vide et Coût de transport plein+c
		instance >> kp;
		instance >> kv;
		instance >> cs;
		instance >> ccd;
		printf("KP %0.3f\t\n", kp);
		printf("KV %0.3f\t\n", kv);
		printf("CS %d\t\n", cs);
		printf("CCD %0.0f\t\n", ccd);
		/**********************************************************************************/
		printf("\n cm\n");
		IloIntArray cm(env, n);
		for (int i = 0; i < n; i++)
			instance >> cm[i];
		//test de lecture cm
		for (int i = 0; i < n; i++)
		printf("%d\t|", cm[i]);
		printf("\n"); printf("\n");
		//preparation  du vecteur qui va contenir les distances entre vn et vm
		IloInt val = 0;
		IloArray< IloIntArray> distNM(env, n);

		for (int i = 0; i < n; i++)
			//for (int j = 0; j < m; j++)
			distNM[i] = IloIntArray(env, m);
		int med = 0;
		int aa = 0;
		int i = 0;
		int j = 0;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				instance >> med;
				if (elig[j] != 0)
				{
					distNM[i][aa] = med;
					if (i == j)
						distNM[i][aa] = 15;
					aa = aa + 1;

				}
				else
					distNM[i][aa] = 0;
			}
			aa = 0;
		}
		//test de lecture de dnm
		printf("\nDnm\n");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				printf("%d\t|", distNM[i][j]);
			printf("\n");
		}
		printf("\n"); printf("\n");
		/***************************************************************************************/
		IloArray< IloIntArray> distMD(env, m);
		for (int i = 0; i < m; i++)
			distMD[i] = IloIntArray(env, d);
		med = 0;
		aa = 0;
		i = 0;
		j = 0;
		int ccc = 0;
		for (i = 0; i<n; i++)
		{
			if (elig[i] == 1)
			{
				for (j = 0; j < d; j++)
				{
					instance >> distMD[aa][j];
				}
				aa++;
			}
			else
				for (j = 0; j < d; j++)
				{
					instance >> med;
				}
		}
		//test de lecture distmd
		printf("\nDmd\n");

		for (i = 0; i < m; i++)
		{
			for (j = 0; j < d; j++)


				printf("%d\t|", distMD[i][j]);
			printf("\n");
		}
		printf("\n");	printf("\n");

		/*****************************************************************************************/
		IloNumArray cd(env, d);
		for (int i = 0; i < d; i++)
			instance >> cd[i];
		//test de lecture cd
		for (int i = 0; i < d; i++)
		printf("%d\t|", cd[i]);
		printf("\n"); printf("\n");
		/*****************************************************************************************/
		IloNumArray limInf(env, n);
		for (int i = 0; i < n; i++)
			instance >> limInf[i];
		for (int i = 0; i < n; i++)
		printf("%d\t|", limInf[i]);
		printf("\n"); printf("\n");
		/*****************************************************************************************/
		IloIntArray limSup(env, n);
		for (int i = 0; i < n; i++)
			instance >> limSup[i];
		printf("\n lim \n");
		for (int i = 0; i < n; i++)
			printf("%d\t|", limSup[i]);
		printf("\n"); printf("\n");
		/****************************************************************************************/
		IloNumArray R(env, n);
		for (int i = 0; i < n; i++)
			instance >> R[i];
		printf("\n R offre\n");
		for (int i = 0; i < n; i++)
			printf("%0.3f|", R[i]);
		printf("\n"); printf("\n");
		printf("tnm\n\n");
		/****************************************************************************************/
		IloArray<IloNumArray>tnm(env, n);
		for (i = 0; i < n; i++)

			tnm[i] = IloNumArray(env, m);

		double med2 = 0;
		aa = 0;
		i = 0;
		j = 0;

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				instance >> med2;
				if (elig[j] != 0)
				{
					tnm[i][aa] = med2;
					aa = aa + 1;

				}
			}
			aa = 0;
		}









		printf("\n tnm \n");
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				printf("%03.1f\t|", tnm[i][j]);
			}
			printf("\n");
		}
		printf("\n"); printf("\n");
		/*****************************************************************************************/

		IloArray<IloNumArray>tmd(env, m);
		for (int i = 0; i < m; i++)
			tmd[i] = IloNumArray(env, d);

		// à verifier
		double med3 = 0;
		aa = 0;
		i = 0;
		j = 0;

		for (i = 0; i <n; i++)
		{
			if (elig[i] == 1)
			{
				for (j = 0; j < d; j++)
				{


					instance >> tmd[aa][j];
				}
				aa++;
			}
			else
			{
				for (j = 0; j < d; j++)
				{
					instance >> med3;
				}
			}



		}


		printf("tmd\n");
		
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < d; j++)
			{
				printf("%03.1f\t|", tmd[i][j]);

			}
			printf("\n");
		}
		printf("\n"); printf("\n");

		/****************************************************************************************/
		//std::string  nomp;
		//Les variables de décision
		//1 xnm
		//1 pnm
		IloArray<IloIntVarArray>pnm(env, n);
		int aze = 0;
		int cc = 0;
		for (int i = 0; i < n; i++)
		{
			cc = 0;
			pnm[i] = IloIntVarArray(env, m);
			for (int j = 0; j < n; j++)
				if (elig[j] == 1)
				{
					std::string nomp = "P" + std::to_string(i + 1) + std::to_string(cc + 1);
					char * cstr = new char[nomp.length() + 1];
					strcpy(cstr, nomp.c_str());
					cstr[nomp.size()] = '\0';
					pnm[i][cc] = IloIntVar(env, 0, 1, cstr);
					
					IloConstraint sens1Pnm(pnm[i][cc]==0);
					IloConstraint sens2Pnm(pnm[i][cc] == 1);
					IloOr orpnm(env);
					orpnm.add(sens1Pnm);
						orpnm.add(sens2Pnm);
						model.add(orpnm);
					/*model.add(sens1Pnm);
					model.add(sens2Pnm);*/
					delete[] cstr;
					cc++;
					printf("teest %d %d\n", i, j);
				}	
			
			IloConstraint ssss(IloSum(pnm[i]) == 1);
			ssss.setName("sens");
			model.add(ssss);
	

		}
		IloArray<IloNumVarArray>xnm(env, n);
		int dd;
		for (int i = 0; i < n; i++)
		{
			dd = 0;
			xnm[i] = IloNumVarArray(env, m);
			for (int j = 0; j < n; j++)
			{
				std::string nomp = "Xnm" + std::to_string(i + 1) + std::to_string(j + 1);
				char * cstr = new char[nomp.length() + 1];
				strcpy(cstr, nomp.c_str());
				cstr[nomp.size()] = '\0';
			
				if (elig[j] == 1)
				{
					xnm[i][dd] = IloNumVar(env, 0, IloInfinity, cstr);
					dd++;
				}
			
				delete[] cstr;
				
				
			}
		}
		//1 xmd
		IloArray<IloNumVarArray>xmd(env, m);
		int ff=0;
		for (int i = 0; i < n; i++)
		{
			if (elig[i] == 1)
			{
			xmd[ff] = IloNumVarArray(env, d);
			for (int j = 0; j < d; j++)
			{
				std::string nomp = "Xmd" + std::to_string(ff + 1) + std::to_string(j + 1);
				char * cstr = new char[nomp.length() + 1];
				strcpy(cstr, nomp.c_str());
				cstr[nomp.size()] = '\0';				
				xmd[ff][j] = IloNumVar(env, 0, IloInfinity, cstr);
				delete[] cstr;
				}
			ff++;
				
				
			}
			
		}

		//1 qmd
		IloArray<IloBoolVarArray>qmd(env, m);
		for (int i = 0; i < m; i++)
		{
			qmd[i] = IloBoolVarArray(env, d);
			for (int j = 0; j < d; j++)
			{
				std::string nomp = "Qmd" + std::to_string(i + 1) + std::to_string(j + 1);
				char * cstr = new char[nomp.length() + 1];
				strcpy(cstr, nomp.c_str());
				cstr[nomp.size()] = '\0';
				qmd[i][j] = IloBoolVar(env, cstr);
				delete[] cstr;
			}
		}

		IloIntVarArray km(env, m);
		for (int i = 0; i < m; i++)
		{
			
			std::string nomp = "KM" + std::to_string(i + 1);
			char * cstr = new char[nomp.length() + 1];
			strcpy(cstr, nomp.c_str());
			cstr[nomp.size()] = '\0';
			km[i] = IloIntVar(env,0,1, cstr);
			delete[]cstr;
			
		}


		//*********y
		IloArray< IloArray<IloIntVarArray>>ynm(env, n);
		for (int i = 0; i < n; i++)
		{
			ynm[i] = IloArray< IloIntVarArray>(env, m);
			for (int j = 0; j < m; j++)
			{

				ynm[i][j] = IloIntVarArray(env, s[i]);
				for (int k = 0; k < s[i]; k++)
				{
					std::string nomp = "Ynm" + std::to_string(i + 1) + std::to_string(j + 1) + std::to_string(k + 1);
					char * cstr = new char[nomp.length() + 1];
					strcpy(cstr, nomp.c_str());
					cstr[nomp.size()] = '\0';
					ynm[i][j][k] = IloIntVar(env,0,1, cstr);
					delete[] cstr;
				}
			}
		}

		//*********ymd
		IloArray< IloArray<IloBoolVarArray>>ymd(env, m);
		for (int i = 0; i < m; i++)
		{
			ymd[i] = IloArray< IloBoolVarArray>(env, d);

			for (int j = 0; j < d; j++)
			{

				ymd[i][j] = IloBoolVarArray(env, s[i]);
				for (int k = 0; k < s[i]; k++)
				{
					std::string nomp = "Ymd" + std::to_string(i + 1) + std::to_string(j + 1) + std::to_string(k + 1);
					char * cstr = new char[nomp.length() + 1];
					strcpy(cstr, nomp.c_str());
					cstr[nomp.size()] = '\0';
					ymd[i][j][k] = IloBoolVar(env, cstr);
					delete[] cstr;
				}
			}
		}

		//*********znm
		IloArray< IloArray<IloNumVarArray>>znm(env, n);
		for (int i = 0; i < n; i++)
		{
			znm[i] = IloArray< IloNumVarArray>(env, m);
			for (int j = 0; j < m; j++)
			{

				znm[i][j] = IloNumVarArray(env, s[i]);
				for (int k = 0; k < s[i]; k++)
				{
					std::string nomp = "Znm" + std::to_string(i + 1) + std::to_string(j + 1) + std::to_string(k + 1);
					char * cstr = new char[nomp.length() + 1];
					strcpy(cstr, nomp.c_str());
					cstr[nomp.size()] = '\0';
					znm[i][j][k] = IloNumVar(env, 0, IloInfinity, cstr);
					delete[] cstr;
				}
			}
		}

		//

		//*********zmd    m lignes et d colonnes, qmd,ymd
		IloArray< IloArray<IloNumVarArray>>zmd(env, m);
		for (int i = 0; i < m; i++)
		{
			zmd[i] = IloArray< IloNumVarArray>(env, d);

			for (int j = 0; j < d; j++)
			{

				zmd[i][j] = IloNumVarArray(env, s[i]);
				for (int k = 0; k < s[i]; k++)
				{
					std::string nomp = "Zmd" + std::to_string(i + 1) + std::to_string(j + 1) + std::to_string(k + 1);
					char * cstr = new char[nomp.length() + 1];
					strcpy(cstr, nomp.c_str());
					cstr[nomp.size()] = '\0';
					zmd[i][j][k] = IloNumVar(env, 0, IloInfinity, cstr);

					delete[] cstr;
				}
			}
		}






		//14

		for (i = 0; i < n; i++)
		{

			for (j = 0; j < m; j++)
			{
				IloExpr cont14(env);
				cont14.setName("Cont14");
				for (int k = 0; k < s[i]; k++)
				{
					cont14 += znm[i][j][k];
				}
				IloConstraint zegxnm(cont14 == xnm[i][j]);
				zegxnm.setName("xnmEznm");
				model.add(zegxnm);
				cont14.end();
			}
		}
		//15

		for (i = 0; i < m; i++)

		{

			for (j = 0; j < d; j++)
			{
				IloExpr cont15(env);
				cont15.setName("Cont15");
				for (int k = 0; k < s[i]; k++)
				{
					cont15 += zmd[i][j][k];
				}
				model.add(cont15 == xmd[i][j]);
				cont15.end();
			}
		}


		//1

		for (i = 0; i < n; i++)
		{
			IloExpr cont1(env);
			cont1.setName("Cont1");
			for (j = 0; j < m; j++)
			{
				cont1 += xnm[i][j];
			}
			std::string nomc = "Cont1." + std::to_string(i + 1);
			char * cstr = new char[nomc.length() + 1];
			strcpy(cstr, nomc.c_str());
			IloConstraint const1(cont1 <= R[i]);
			const1.setName(cstr);
			model.add(const1);//==
			cont1.end();

		}

		//2
		/*****************************************verif*/
		for (i = 0; i < d; i++)
		{
			IloExpr cont2(env);
			for (j = 0; j < m; j++)
			{
				cont2 += xnm[j][i];
			}
			std::string nomc = "Cont2." + std::to_string(i + 1);
			char * cstr = new char[nomc.length() + 1];
			strcpy(cstr, nomc.c_str());
			IloConstraint const2(cont2 <= cd[i]);
			const2.setName(cstr);
			model.add(const2);//==
			cont2.end();
		}
		//3
		/*
		IloInt j, k;
		j = n - 1; k = d - 1;
		while (j >= 0 || k >= 0)
		{
		IloExpr cont31(env);
		IloExpr cont32(env);
		cont31 = IloSum(xnm[j]);
		if(k>=0)
		cont32 = IloSum(xmd[k]);

		IloConstraint const3(cont31 == cont32);
		const3.setName("Cont3");
		model.add(const3);
		cont31.end();
		cont32.end();
		j--; d--;



		*/

		for (i = 0; i < m; i++)
		{
			IloExpr cont31(env);
			IloExpr cont32(env);
			for (j = n - 1; j >= 0; j--)
			{
				//cont31 += xnm[j][i];
				cont31 += IloSum(xnm[j]);
			}
			for (j = d - 1; j >= 0; j--)
			{
				cont32 += IloSum(xmd[j]);
			}
			IloConstraint const3(cont31 == cont32);
			const3.setName("Cont3");
			model.add(const3);
			cont31.end();
			cont32.end();

		}





		//4
		/*
		for (i = 0; i < n; i++)
		{
		IloBoolExpr cont4(env);



		cont4 = IloSum(pnm[i]);
		std::string nomc = "Cont4." + std::to_string(i + 1);
		char * cstr = new char[nomc.length() + 1];
		strcpy(cstr, nomc.c_str());
		IloConstraint const4(cont4 <=1);
		const4.setName(cstr);

		model.add(const4);//a verif
		cont4.end();
		}*/

		Z = 65535;

		for (i = 0; i < n; i++)
		{
			IloExpr pnmz(env);
			pnmz.setName("Cont5");
			for (int f = 0; f<m; f++)
			{
				pnmz = pnm[i][f] * Z;
				IloConstraint const5(pnmz >= xnm[i][f]);
				const5.setName("Const5");
				model.add(const5);//>=

			}

			pnmz.end();
		}
		//7

		for (i = 0; i < m; i++)
		{
			IloExpr cont7(env);
			cont7.setName("Cont7");
			for (j = 0; j < n; j++)
			{
				cont7 += xnm[j][i];
			}

			model.add(cont7 <= cm[i]);//<=
			cont7.end();
		}
		//8

		for (i = 0; i < m; i++)
		{
			IloExpr cont8(env);
			cont8.setName("Cont8");
			for (j = 0; j < d; j++)
				cont8 += qmd[i][j];
			model.add(cont8 == 1);//a verif
			cont8.end();
		}
		//9



		for (int k = 0; k < m; k++)
		{
			for (i = 0; i < d; i++)
			{
				IloExpr cont9(env);
				cont9.setName("Cont9");
				cont9 += qmd[k][i] * tmd[k][i];
				for (j = 0; j < n; j++)
					cont9 += pnm[j][k] * tnm[j][k];

				cont9 += tcd;
				model.add(cont9 <= ts);
				cont9.end();
			}
		}

		//10
		
	

		IloExpr cont10(env);
		cont10.setName("Cont10");
		for (i = 0; i < km.getSize(); i++)
		{

			cont10 += km[i];

		}
		model.add(cont10 <= m);
		cont10.end();
		//11

		for (i = 0; i < n; i++)
		{
			IloExpr cont11(env);
			cont11.setName("Cont11");
			for (j = 0; j < m; j++)
			{
				cont11 = km[j] * Z;
				model.add(cont11 >= xnm[i][j]);
				
			}
			cont11.end();
			//cont11 ;
		}
		//12

		IloNum p1, p2;
		IloRange intr;
		for (i = 0; i < n; i++)
		{
			IloExpr cont12(env);
			cont12.setName("Cont12");
			for (j = 0; j < m; j++)
				for (int k = 0; k < s[i]; k++)
				{
					/*p1 = limInf[k] * ynm[i][j][k];
					p2 = limSup[k] * ynm[i][j][k];*/
					cont12 = znm[i][j][k];
					/*intr.setLb(p1);
					intr.setUb(p2);*/
					model.add(cont12 >= limInf[k] * ynm[i][j][k]);
					model.add(cont12 <= limSup[k] * ynm[i][j][k]);
					
				}
			cont12.end();
		}

		//13

		IloNum p11, p22;
		IloRange intr1;
		for (i = 0; i < m; i++)
		{
			IloExpr cont13(env);
			cont13.setName("Cont13");
			for (j = 0; j < d; j++)
				for (int k = 0; k < s[i]; k++)
				{
					/*p11 = limInf[k] * ymd[i][j][k];
					p22 = limSup[k] * ymd[i][j][k];*/
					cont13 = zmd[i][j][k];
					/*intr1.setLb(p11);
					intr1.setUb(p22);*/
					model.add(cont13 >= limInf[k] * ymd[i][j][k]);
					model.add(cont13 <= limSup[k] * ymd[i][j][k]);
					
				}
			cont13.end();
		}

		//16

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				IloExpr cont16(env);
				cont16.setName("Cont16");
				for (int k = 0; k < s[i]; k++)
				{
					cont16 += ynm[i][j][k];
				}
				model.add(cont16 <= 1);
				cont16.end();
			}
		}
		//15

		for (i = 0; i < m; i++)
		{
			for (j = 0; j < d; j++)
			{
				IloExpr cont17(env);
				cont17.setName("Cont17");
				for (int k = 0; k < s[i]; k++)
				{
					cont17 += ymd[i][j][k];
				}
				model.add(cont17 == 1);
				cont17.end();
			}
		}


		//jjjjjjjjjjjjjj
		/**************************************************************************************/
		// fragment 1
		IloExpr fo(env);
		IloNum coutnm = 0;
		IloNumExpr f1(env);
		//int ii, jj;
		IloArray<IloNumExprArray> vct(env, n);

		for (i = 0; i < n; i++)
		{

			vct[i] = IloNumExprArray(env, m);
			f1 = IloNumExpr(env);
			for (j = 0; j < m; j++)
			{
				vct[i][j] = IloNumExpr(env);
				for (int ss = 0; ss < s[i]; ss++)
				{

					vct[i][j] += (((kp - kv) / (cs*s[i]))*znm[i][j][ss] + kv*s[i] * ynm[i][j][ss])*distNM[i][j];
					f1 += vct[i][j];
				}



			}
			//fo += IloSum(vct[i]);
			fo += f1;
		}

		/****************************************************/
		//ct(xmd)
		IloNumExpr f2(env);
		//int ii, jj;
		IloArray<IloNumExprArray> vct2(env, m);

		for (i = 0; i < m; i++)
		{

			vct2[i] = IloNumExprArray(env, d);
			f2 = IloNumExpr(env);
			for (j = 0; j < d; j++)
			{
				vct2[i][j] = IloNumExpr(env);
				for (int ss = 0; ss < s[i]; ss++)
				{

					vct2[i][j] += (((kp - kv) / (cs*s[i]))*zmd[i][j][ss] + kv*s[i] * ymd[i][j][ss])*distMD[i][j];
					f2 += vct2[i][j];
					//printf("%d   %d-%d-%d\n", distMD[j][i]);
				}



			}
			//fo += IloSum(vct[i]);
			fo += f2;
		}


		//IloCplex cplex(env);
		//cplex.getValue(fo);    

		IloNumArray f3(env, m);
		for (i = 0; i < m; i++)
			fo += km[i] * couv[i];

		IloExprArray f4(env, m);
		IloExpr f44(env);
		int med5 = 0;
		int aa2 = 0;
		int i2 = 0;
		int j2 = 0;

		for (i2 = 0; i2 < m; i2++)
		{
			f4[i2] = IloExpr(env);
			if (elig[i2] != 0)
			{
				for (j2 = 0; j2 < n; j2++)
					f4[i2] += xnm[j2][i2] * pnm[j2][i2];
				f4[i2] += f4[i2] * ccd;
			}

		}
		fo += IloSum(f4);

		IloObjective obje(env, fo, IloObjective::Minimize);
		obje.setName("FObjective");
		model.add(obje);





		cplex.extract(model);


		cplex.exportModel("E:\diet.lp");
		//cplex.getValue(pnm[0][0]);
		//cplex.presolve(IloCplex::Algorithm::Network );
		
		if (cplex.solve())
		{
			env.out() << "Resultat: " << cplex.getStatus() << endl;
			
			printf("cost =%.5f\n",cplex.getObjValue(1));
		
			
			printf("best =%.5f\n", cplex.getBestObjValue());
			printf("\n Les Xnm------------------\n");
			IloArray <IloNumArray> resXnm(env, n);
			for (int i = 0; i < n; i++)
			{
				resXnm[i]= IloNumArray(env, m);
				cplex.getValues(resXnm[i], xnm[i],2);
			}
			for (int i = 0; i < n; i++)
			{
				for(int mp=0;mp<m;mp++)
				env.out() << resXnm[i][mp] << "\t"; 
				printf("\n");
			}
			IloArray< IloArray<IloNumArray>> resZnm(env,n);
			printf("\n Les znm------------------\n");
			for (int i = 0; i < n; i++)
			{
				resZnm[i] = IloArray< IloNumArray>(env, m);
				for (int j = 0; j < m; j++)
				{
					resZnm[i][j] = IloNumArray(env, s[i]);		

						cplex.getValues(resZnm[i][j], znm[i][j],2);
					
				}
			}
			for (int i = 0; i < n; i++)
			{
				for (int mp = 0; mp<m; mp++)
					for(int k=0;k<s[i];k++)
					env.out() << resZnm[i][mp][k] << "\t";
				printf("\n");
			}


			printf("\n Les Qmd------------------\n");
			IloArray <IloNumArray> resQmd(env, m);
			for (int i = 0; i < m; i++)
			{
				resQmd[i] = IloNumArray(env, d);
				cplex.getValues(resQmd[i], qmd[i],2);
			}
			for (int i = 0; i < m; i++)
			{
				
					env.out() << resQmd[i] << "\t";
				printf("\n");
			}
			printf("\n Les Km------------------\n");

			IloNumArray resKm(env, m);
		    cplex.getValues(km,resKm,2);
			env.out() << resKm << "\t";
			printf("\n Les Pnm------------------\n");
			IloArray <IloNumArray> resPnm(env, n);
			for (int i = 0; i < n; i++)
			{
				resPnm[i] = IloNumArray(env, m);
				cplex.getValues(resPnm[i], pnm[i],2);
			}
			for (int i = 0; i < n; i++)
			{
				for (int mp = 0; mp<m; mp++)
					env.out() << resPnm[i][mp] << "\t";
				printf("\n");
			}
			




			
		}
		getchar();
	}
	catch (IloException& ex) {
		//cerr << "erreur cplex: " << ex.getMessage() << endl;
		printf("\n%s", ex.getMessage());
		getchar();

	}
	catch (...) {
		//cerr << "erreur cpp: " <<  endl;
		printf("Erreur CPP %s");

	}
	env.end();
}


