#include <stdio.h>
#include <string.h>
#include "../include/tcalendario.h"

TCalendario::TCalendario(){
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

TCalendario::TCalendario(int dia, int mes, int anyo, char * mens){
    bool bien = Correcto(dia, mes, anyo);
    if(bien == true){
        this->dia = dia;
        this->mes = mes;
        this->anyo = anyo;
        if(mens == NULL){
            mensaje = NULL;
        }
        else{
            mensaje = new char[strlen(mens) + 1];
            strcpy(mensaje, mens);
        }
    }
    else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        mensaje = NULL;
    }
}

TCalendario::TCalendario(const TCalendario &origen){
    dia = origen.dia;
    mes = origen.mes;
    anyo = origen.anyo;
    if(origen.mensaje == NULL){
        mensaje = NULL;
    }
    else{
        mensaje = new char[strlen(origen.mensaje) + 1];
        strcpy(mensaje, origen.mensaje);
    }
}

TCalendario::~TCalendario(){
    dia = 1;
    mes = 1;
    anyo = 1900;
    if(mensaje != NULL){
        delete [] mensaje;
        mensaje = NULL ;
    }
}

TCalendario& TCalendario::operator=(const TCalendario &de){
    if(this != &de){
        dia = de.dia;
        mes = de.mes;
        anyo = de.anyo;
        if(de.mensaje == NULL){
            delete [] mensaje;
            mensaje = NULL;
        }
        else{
            mensaje = new char [strlen(de.mensaje) + 1];
			strcpy(mensaje, de.mensaje);
        }
    }
    return *this;
}

TCalendario TCalendario::operator+(int de){
    int i;
    bool bisiesto = false;
    TCalendario r(*this);

    if(de > 0){
        for(i = 1; i <= de; i++){
            ++r;
        }
    }
    return r;
}

TCalendario TCalendario::operator-(int de){
    int i;
    TCalendario r(*this);

    if(de > 0){
        for(i = 1; i <= de; i++){
            --r;
        }
            
    }
    return r;
}



TCalendario TCalendario::operator++(int de){
    TCalendario r(*this);
    ++(*this);
    return r;
}

TCalendario &TCalendario::operator++(){
    bool bisiesto = false;
    if(anyo%4==0 && anyo%100!=100 || anyo%400==0){
        bisiesto = true;
    }
    if(dia == 28 && mes == 2){
        if(bisiesto){
            dia++;
        }
        else{
            dia = 1;
            mes++;
        }
    }
    else{
        if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
            if(dia == 31){
                if(mes == 12){
                    dia = 1;
                    mes = 1;
                    anyo++;
                }
                else{
                    dia = 1;
                    mes++;
                }
            }
            else{
                dia++;
            }
        }
        else{
            if(dia == 29 && mes == 2){
                dia = 1;
                 mes++;
            }
            else{
                if(dia == 30){
                    dia = 1;
                    mes++;
                }
                else{
                    dia++;
                }
            }
        }
    }
    return *this;
}

TCalendario TCalendario::operator--(int de){
    TCalendario r(*this);
	 --(*this);
	return r;
}

TCalendario &TCalendario::operator--(){
    bool bisiesto = false;
    if(anyo%4==0 && anyo%100!=100 || anyo%400==0){
        bisiesto = true;
    }
    if(dia == 1 && mes == 3){
        if(bisiesto){
            dia = 29;
            mes--;
        }
        else{
            dia = 28;
            mes--;
        }
    }
    else{
        if(dia == 1 && (mes == 1 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)){
            if(mes == 1){
                if(anyo == 1900){
                    dia = 1;
                    mes = 1;
                    if(mensaje != NULL){
                        delete [] mensaje;
                        mensaje = NULL;
                    }
                }
                else{
                    dia = 31;
                    mes = 12;
                    anyo--;
                }
            }
            else{
                if(dia == 1){
                    dia = 30;
                    mes--;
                }
                else{
                    dia--;
                }
            }
        }      
        else{
            if(dia == 1){
                dia = 31;
                mes--;
            }
            else{
                dia--;
            }
        }
    }
	return *this;
}










bool TCalendario::Correcto(int dia, int mes, int anyo){
    bool bisiesto = false;
    bool bien = false;

    if(anyo%4==0 && anyo%100!=100 || anyo%400==0){
        bisiesto = true;
    }
    
    if(dia > 0 && dia < 32 && mes > 0 && mes < 13 && anyo >= 1900){

        if((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 
        || mes == 10 || mes == 12)){
			bien = true;
        }
        else{
            if(mes == 2 && dia < 30 && bisiesto){
                bien = true;
            }          
            else{ 
                if(mes ==2 && dia < 29 && !bisiesto){
                    bien = true;
                }
                else{
                    if(mes != 2 && dia < 31){
                        bien = true;
                    }  
                }
            }
        }
    }
    return bien;
}

bool TCalendario::ModFecha (int d, int m, int a){
    bool es = false;
    es = Correcto(d, m, a);
    if(es){
        this->dia = d;
        this->mes = m;
        this->anyo = anyo;
    }
    return es;
}

bool TCalendario::ModMensaje(char *mens){
    bool mod = false;
    if(mens == NULL){
        mod = true;
        mensaje = NULL;
    }
    else{
        if(mensaje!= NULL){
			delete [] mensaje;
		}
        mensaje = NULL;
        mensaje = new char[strlen(mens) + 1];
        strcpy(mensaje, mens);
        mod = true;
    }
    return mod;
}









bool TCalendario::operator==(const TCalendario &de) const{
    bool es = false;
    if(&de && this){
        if(dia == de.dia && mes == de.mes && anyo == de.anyo){
            if(de.mensaje == NULL){
                if(mensaje == NULL){            
                    es = true;
                }
            }
            else{
                if(de.mensaje!=NULL && mensaje!=NULL){
                    if(strcmp(de.mensaje, mensaje) == 0){
                        es = true;
                    }
                }
            }  
        }
    }
    return es;
}


bool TCalendario::operator!=(const TCalendario &de) const{
    return !(*this == de);
}

bool TCalendario::operator>(const TCalendario &de) const{
    
    bool mayor = false;
    if(anyo > de.anyo){
        mayor = true;
    }
    else{
        if(anyo == de.anyo){
           if(mes > de.mes){
				mayor = true;
			}
            else{
				if(mes == de.mes){
					if(dia > de.dia){
						mayor = true;
					}
                    else{
                        if(dia==de.dia){
                            if(mensaje != NULL && de.mensaje == NULL){
                                mayor = true;
                            }           
                            else{
                                if(mensaje != NULL && de.mensaje != NULL){
                                    if(strcmp(mensaje, de.mensaje) > 0){
                                        mayor = true;
                                    }
                                }
                            }
                        }
                    }
                }          
            }
        }
    }
    return mayor;
}


bool TCalendario::operator<(const TCalendario &de) const{
    return !(*this > de || *this == de);
}








bool TCalendario::EsVacio(){
    bool es = false;
    if(dia == 1 && mes == 1 && anyo == 1900 && mensaje == NULL){
        es = true;
    }
    return es;
}

int TCalendario::Dia() const{
    return dia;
}

int TCalendario::Mes() const{
    return mes;
}

int TCalendario::Anyo() const{
    return anyo;
}

char *TCalendario::Mensaje()const{
    if(mensaje == NULL){
        return NULL;
    }
    else{
        return mensaje;
    }
}


ostream & operator<<(ostream &os, const TCalendario &c){
    if(c.dia < 10){

        os << "0" << c.dia << "/" ; 
        if(c.mes < 10){
            os << "0" << c.mes << "/" << c.anyo << " "; 
        }
        else{
            os << c.mes << "/" << c.anyo << " ";
        } 
    }
    else{     
        os << c.dia << "/" ;
        if(c.mes < 10){
            os << "0" << c.mes << "/" << c.anyo << " "; 
        }
        else{
            os << c.mes << "/" << c.anyo << " ";
        } 
    }
    if(c.mensaje == NULL){
        os << '"' << '"';
    }
    else{
        os << '"' << c.mensaje << '"';
    }
    return os;
}