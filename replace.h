#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//idk guide
// use only dynamically allocated so your field should to contain an ptr address, the use in this case should be like &chararr, when chararr is mallocated ptr that 0 terminated, and can be reassigned either undefined behaviour;
// function should get &str as input, if len changes it will reassign a new mallocated ptr else stays same place, static in plans



//algorithm utilization O(2n)
size_t len(char*arr) {
    size_t i=0;
    while (arr[i] != 0)i++;
    return i;
}

//algorithm utilization up to O(2square(n))
size_t countStream(const char* inwhat, const char* bywhat) {
    size_t
        idx = 0,
        jdx = 0,
        kdx = 0,
        bywhatlen = len(bywhat);
    while (inwhat[idx] != 0) {
        if (inwhat[idx] == bywhat[jdx]) {
            jdx++;
            if (jdx == bywhatlen) {
                kdx++;
                jdx = 0;
            }

        }else jdx = 0;
        idx++;
    }
    return kdx;
}


size_t replaced(const char**inwhat,const char*bywhat,const char*by) {
    char keys=0;
    size_t
        kdxjdx,
        jdxkdx,
        idx = 0,
        jdx = 0,
        kdx = 0,
        bylen = by?len(by) : 0,
        inwhatlen = len(*inwhat),
        bywhatlen = len(bywhat),
        countbywhat = countStream(*inwhat, bywhat);
    if ((!(*inwhat)) ||(!inwhat) || (!bywhat) || (!inwhatlen) || (!bywhatlen))return 0;
    kdx = countbywhat*bywhatlen;
    jdx = countbywhat*bylen;
    idx = inwhatlen;
    kdxjdx = kdx - jdx;
    jdxkdx = jdx - kdx;
    //Why there is if? either ternary operator will be too embedded // this is not a problem of course im just laze
    if (kdx>jdx) {
        idx = inwhatlen - kdxjdx;
        keys = 1;
    }
    else if (jdx>kdx) {
        keys = 2;
        idx = inwhatlen + jdxkdx;
    }
    char* tmp = malloc(idx+1);
    tmp[idx] = 0;
    //idx = 0;
    jdx = 0;
    kdx = 0;
    size_t rs = 0, vr = 0;
    switch (keys) {
    case 1:
        idx = 0;
        //kdx>jdx
        if (((bywhatlen==inwhatlen)&&strcmp(bywhat,*inwhat)) && (bylen == 0)) {
            tmp[0] = 0;
            free(*inwhat);
            *inwhat=tmp;
            return 1;
        }
        rs = bywhatlen - bylen;
        while ((*inwhat)[idx] != 0) {
            tmp[idx + vr] = (*inwhat)[idx];
            if ((*inwhat)[idx] == bywhat[jdx]) {
                jdx++;
                if (jdx == bywhatlen) {
                    kdx++;
                    strcpy((tmp + idx + vr+1) - bywhatlen, by);
                    jdx = 0;
                    vr -= rs;
                }

            }
            else jdx = 0;
            idx++;
        }
        free(*inwhat);
        *inwhat = tmp;
        return kdx;
        break;
    case 2:
        idx = 0;
        //jdx>kdx
        rs = bylen - bywhatlen;
        while ((*inwhat)[idx] != 0) {
            tmp[idx+vr] = (*inwhat)[idx];
            if ((*inwhat)[idx] == bywhat[jdx]) {
                jdx++;
                if (jdx == bywhatlen) {
                    kdx++;
                    memcpy((tmp + idx+vr+1) - bywhatlen, by,bylen);
                    jdx = 0;
                    vr += rs;
                }

            }
            else jdx = 0;
            idx++;
        }
        free(*inwhat);
        *inwhat = tmp;
        return kdx;
        break;
    case 0:
        //kdx==jdx
        //strcpy(tmp,*inwhat);

        idx = 0;
        while ((*inwhat)[idx] != 0) {
            if ((*inwhat)[idx] == bywhat[jdx++]) {
                if (jdx == bywhatlen) {
                    memcpy((*inwhat) + idx-1, by,bylen);
                    kdx++;
                    jdx = 0;
                }

            }else jdx = 0;
            idx++;
        }
        //free(*inwhat);
        //*inwhat = tmp;
        return kdx;
        break;
    default:
        printf("there can't be an default in switch case\n");
    }
}
