
#include "DLists.h"
#include "CSV.h"

DLIndex::DLIndex(ECampos pType)
{
    aType = pType;
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // Constructor

DLIndex::~DLIndex(void)
{
    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DLIndex::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DLIndex::push_front(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        PDNODE lTemp = getNewNode(pData);
        aHead->sPrev = lTemp;
        lTemp->sNext = aHead;
        aHead = lTemp;
    }
} // push_front

void DLIndex::push_back(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        PDNODE lTemp = getNewNode(pData);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
} // push_back

void DLIndex::push(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        if (comp(pData, aHead->sData) <= 0)
            push_front(pData);
        else if (comp(pData, aTail->sData) >= 0)
            push_back(pData);
        else {
            PDNODE lItem = search(pData);
            if (lItem) {
                PDNODE lTemp = getNewNode(pData);
                lTemp->sNext = lItem;
                lTemp->sPrev = lItem->sPrev;
                lItem->sPrev->sNext = lTemp;
                lItem->sPrev = lTemp;
            }
        }
    }
} // push

PDATA DLIndex::get(bool pRev)
{
    PDATA lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL)
            aCurr = (pRev == false ? aHead : aTail);
        else
            aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
        if (aCurr)
            lTemp = aCurr->sData;
    }

    return lTemp;
} // get

void DLIndex::resetCurr(void)
{
    aCurr = NULL;
} // resetCurr

void DLIndex::pop_front(void)
{
    if (aHead) {
        PDNODE lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;
        if (aHead) {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
        else {
            aTail = NULL;
            aCurr = NULL;
        }
    }
} // pop_front

void DLIndex::pop_back(void)
{
    if (aHead) {
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if (aTail) {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }
    }
} // pop_back

void DLIndex::del(PDATA pData)
{
    if (aHead) {
        if (aHead->sData == pData)
            pop_front();
        else if (aTail->sData == pData)
            pop_back();
        else {
            PDNODE lTemp = find(pData);
            if (lTemp) {
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                delete lTemp;
            }
        }
    }
} // del

bool DLIndex::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DLIndex::repr(bool pRev)
{
    if (aHead) {
        PDNODE lTemp = (pRev == false ? aHead : aTail);
        while (lTemp) {
            cout << " -> ";
            if (lTemp->sData) {
                cout << "[(" << lTemp->sData->sID;
                cout << ") " << lTemp->sData->sNombre;
                cout << ", " << lTemp->sData->sApellido;
                cout << ", " << lTemp->sData->sUsuario;
                cout << ", " << lTemp->sData->sTarjeta;
                cout << ", " << lTemp->sData->sSaldo << "]";
            }
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << " ->|| " << endl;
    }
} // repr

PDNODE DLIndex::search(string pVal)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (comp(pVal, lTemp->sData) <= 0)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DLIndex::search(unsigned long int pID)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pID <= lTemp->sData->sID)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DLIndex::find(PDATA pData)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pData == lTemp->sData)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find

PDNODE DLIndex::search(PDATA pData)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (comp(pData, lTemp->sData) <= 0)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DLIndex::getNewNode(PDATA pData)
{
    PDNODE lTemp = new DNODE;

    if (lTemp) {
        lTemp->sData = pData;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode

int DLIndex::comp(PDATA pA, PDATA pB)
{
    int lRes = 0;

    switch (aType) {
        case ECampos::index:
            if (pA->sID < pB->sID) lRes = -1;
            else if (pA->sID == pB->sID) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::nombre:
            if (pA->sNombre < pB->sNombre) lRes = -1;
            else if (pA->sNombre == pB->sNombre) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::apellido:
            if (pA->sApellido < pB->sApellido) lRes = -1;
            else if (pA->sApellido == pB->sApellido) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::usuario:
            if (pA->sUsuario < pB->sUsuario) lRes = -1;
            else if (pA->sUsuario == pB->sUsuario) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::contrasena:
            if (pA->sCont < pB->sCont) lRes = -1;
            else if (pA->sCont == pB->sCont) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::tarjeta:
            if (pA->sTarjeta < pB->sTarjeta) lRes = -1;
            else if (pA->sTarjeta == pB->sTarjeta) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::saldo:
            if (pA->sSaldo < pB->sSaldo) lRes = -1;
            else if (pA->sSaldo == pB->sSaldo) lRes = 0;
            else lRes = 1;
            break;
    }

    return lRes;
} // comp

int DLIndex::comp(string pVal, PDATA pB)
{
    int lRes = 0;
    unsigned long int lValI = 0;
    double lValD = 0;

    switch (aType) {
        case ECampos::index:
            lValI = stol(pVal);
            if (lValI < pB->sID) lRes = -1;
            else if (lValI == pB->sID) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::nombre:
            if (pVal < pB->sNombre) lRes = -1;
            else if (pVal == pB->sNombre) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::apellido:
            if (pVal < pB->sApellido) lRes = -1;
            else if (pVal == pB->sApellido) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::usuario:
            if (pVal < pB->sUsuario) lRes = -1;
            else if (pVal == pB->sUsuario) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::contrasena:
            if (pVal < pB->sCont) lRes = -1;
            else if (pVal == pB->sCont) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::tarjeta:
            if (lValI < pB->sTarjeta) lRes = -1;
            else if (lValI == pB->sTarjeta) lRes = 0;
            else lRes = 1;
            break;
        case ECampos::saldo:
            lValD = stod(pVal);
            if (lValD < pB->sSaldo) lRes = -1;
            else if (lValD == pB->sSaldo) lRes = 0;
            else lRes = 1;
            break;
    }

    return lRes;
} // comp


//---------------


DList::DList(void)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;

    aCurrID = 0;

    aID = new DLIndex(ECampos::index);
    aNom = new DLIndex(ECampos::nombre);
    aApe = new DLIndex(ECampos::apellido);
    aUsu= new DLIndex(ECampos::usuario);
    aCont = new DLIndex(ECampos::contrasena);
    aTar = new DLIndex(ECampos::tarjeta);
    aSal = new DLIndex(ECampos::saldo);

} // Constructor

DList::~DList(void)
{
    delete aID;
    delete aNom;
    delete aApe;
    delete aUsu;
    delete aCont;
    delete aTar;
    delete aSal;

    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DList::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        if (aHead->sData)
            delete aHead->sData;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DList::push_back(string pNombre, string pApellido, 
     string pUsuario, string pContrasena, int pTarjeta, double pSaldo)
{
    if (aHead == NULL) {
        aHead = getNewNode(pNombre, pApellido, pUsuario, pContrasena, pTarjeta, pSaldo);
        aTail = aHead;

        aID->push(aHead->sData);
        aNom->push(aHead->sData);
        aApe->push(aHead->sData);
        aUsu->push(aHead->sData);
        aCont->push(aHead->sData);
        aTar->push(aHead->sData);
        aSal->push(aHead->sData);
    }
    else {
        PDNODE lTemp = getNewNode(pNombre, pApellido, pUsuario, pContrasena, pTarjeta, pSaldo);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;

        aID->push(lTemp->sData);
        aNom->push(lTemp->sData);
        aApe->push(lTemp->sData);
        aUsu->push(aHead->sData);
        aCont->push(aHead->sData);
        aTar->push(aHead->sData);
        aSal->push(aHead->sData);
    }
} // push_back

PDATA DList::get(ECampos pCampo, bool pRev)
{
   PDATA lTemp = NULL;

   switch (pCampo) {
       case ECampos::index: lTemp = aID->get(pRev); break;
       case ECampos::nombre: lTemp = aNom->get(pRev); break;
       case ECampos::apellido: lTemp = aApe->get(pRev); break;
       case ECampos::usuario: lTemp = aUsu->get(pRev); break;
       case ECampos::contrasena: lTemp = aCont->get(pRev); break;
       case ECampos::tarjeta: lTemp = aTar->get(pRev); break;
       case ECampos::saldo: lTemp = aSal->get(pRev); break;

   }

   return lTemp;
} // get

void DList::resetCurr(void)
{
    aID->resetCurr();
    aNom->resetCurr();
    aApe->resetCurr();
    aUsu->resetCurr();
    aCont->resetCurr();
    aTar->resetCurr();
    aSal->resetCurr();
} // resetCurr

void DList::del(string pNombre, string pApellido, string pUsuario, string pContrasena, int pTarjeta, double pSaldo)
{
    if (aHead) {
        PDNODE lItem = find(pNombre, pApellido, pUsuario, pContrasena, pTarjeta, pSaldo);
        if (lItem) {
            del(lItem->sData);
        }
    }
} // del

void DList::del(unsigned long int pID)
{
    if (aHead) {
        PDNODE lItem = aID->search(pID);
        if (lItem && (lItem->sData->sID == pID)) {
            del(lItem->sData);
        }
    }
} // del

bool DList::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DList::repr(ECampos pCampo, bool pRev)
{
    switch (pCampo) {
        case ECampos::index: aID->repr(pRev); break;
        case ECampos::nombre: aNom->repr(pRev); break;
        case ECampos::apellido: aApe->repr(pRev); break;
        case ECampos::usuario: aUsu->repr(pRev); break;
        case ECampos::contrasena: aCont->repr(pRev); break;
        case ECampos::tarjeta: aTar->repr(pRev); break;
        case ECampos::saldo: aSal->repr(pRev); break;
    }
} // repr

void DList::read(string pPath)
{
    CSVReader lReader = CSVReader(pPath);

    TCSVTbl lTbl = lReader.read();

    if (lTbl.size() > 0) {
        for (size_t lCol = 0; lCol < lTbl.size(); lCol++) {
            push_back(lTbl[lCol][0], lTbl[lCol][1], lTbl[lCol][2], lTbl[lCol][3], stod(lTbl[lCol][4]), stod(lTbl[lCol][5]));
        }
    }
} // read

void DList::write(string pPath)
{
    if (aHead) {
        CSVWriter lWriter = CSVWriter(pPath);
        PDNODE lTemp = aHead;
        while (lTemp) {
            lWriter.write(lTemp->sData->sNombre);
            lWriter.write(lTemp->sData->sApellido);
            lWriter.write(lTemp->sData->sUsuario);
            lWriter.write(to_string(lTemp->sData->sSaldo));
            lWriter.writeeol();
            lTemp = lTemp->sNext;
        }
    }
} // write

void DList::pop_front(void)
{
    if (aHead) {
        PDNODE lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        if (aHead->sData)
            delete aHead->sData;
        delete aHead;
        aHead = lTemp;
        if (aHead) {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
        else {
            aTail = NULL;
            aCurr = NULL;
        }
    }
} // pop_front

void DList::pop_back(void)
{
    if (aHead) {
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        if (aTail->sData)
            delete aTail->sData;
        delete aTail;
        aTail = lTemp;
        if (aTail) {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }
    }
} // pop_back

void DList::del(PDATA pData)
{
    if (pData) {
        aID->del(pData);
        aNom->del(pData);
        aApe->del(pData);
        aUsu->del(pData);
        aCont->del(pData);
        aTar->del(pData);
        aSal->del(pData);

        PDNODE lItem = find(pData);
        if (lItem) {
            if (lItem == aHead)
                pop_front();
            else if (aTail == lItem)
                pop_back();
            else {
                if (aCurr == lItem)
                    aCurr = lItem->sNext;
                lItem->sPrev->sNext = lItem->sNext;
                lItem->sNext->sPrev = lItem->sPrev;
                if (lItem->sData)
                    delete lItem->sData;
                delete lItem;
            }
        }
    }
} // del

PDNODE DList::find(PDATA pData)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pData == lTemp->sData)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find

PDNODE DList::find(string pNombre, string pApellido, string pUsuario, string pContrasena, int pTarjeta, double pSaldo)
{
    PDNODE lItem = aNom->search(pNombre);

    if (lItem && (lItem->sData->sNombre == pNombre)) {
        bool lFound = false;
        do {
            PDATA lData = lItem->sData;
            if (lData->sNombre == pNombre) {
                if (
                    (lData->sApellido == pApellido) &&
                    (lData->sUsuario == pUsuario) &&
                    (lData->sCont == pContrasena) &&
                    (lData->sTarjeta==pTarjeta) &&
                    (lData-> sSaldo == pSaldo)
                    )
                    lFound = true;
                if (lFound == false)
                    lItem = lItem->sNext;
            }
            else {
                lItem = NULL;
            }
        } while (lItem && (lFound == false));
        if (lFound == false)
            lItem = NULL;
    }
    else {
        lItem = NULL;
    }

    return lItem;
} // find

PDNODE DList::getNewNode(string pNombre, string pApellido, 
     string pUsuario, string pContrasena, int pTarjeta, double pSaldo)
{
    PDNODE lTemp = new DNODE;

    if (lTemp) 
    {
        lTemp->sData = new DATA;
        if (lTemp->sData) 
        {
            aCurrID++;
            lTemp->sData->sID = aCurrID;
            lTemp->sData->sNombre = pNombre;
            lTemp->sData->sApellido = pApellido;
            lTemp->sData->sUsuario = pUsuario;
            lTemp->sData->sCont = pContrasena;
            lTemp->sData->sTarjeta = pTarjeta;
            lTemp->sData->sSaldo = pSaldo;
        }
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode

