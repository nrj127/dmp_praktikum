#include "onlinegmr.h"
#include <stdio.h>

using namespace std;

onlineGMR::onlineGMR(char* inputFile, char* outputFile) : inputFile(inputFile), outputFile(outputFile)
{

}


void onlineGMR::readMatlabFile()
{
    MATFile *pmat;
    const char* name= inputFile;
    mxArray *pa;

    /* open mat file and read it's content */
    pmat = matOpen( name, "r");
    if (pmat == NULL)
    {
        cout << "Error Opening File: " << name << endl;
        return;
    }

    /* Read in each array. */
    pa = matGetNextVariable(pmat, &name);
    while (pa!=NULL)
    {
        /*
        * Diagnose array pa
        */
        printf("\nArray %s has %d dimensions.", name,
               (int)mxGetNumberOfDimensions(pa));

        //print matrix elements
        // mlfPrintMatrix(pa);

        //get next variable
        pa = matGetNextVariable(pmat,&name);

        //destroy allocated matrix
        mxDestroyArray(pa);
    }

    matClose(pmat);
}

void onlineGMR::writeMatlabFile()
{
    // TODO: Dummy implementation to write to a new matlab file


    MATFile *pmat;

    //create a new mat-file and save some variable/matrix in it
    double dbl1[]={1.1, 4.3, -1.6, -4, -2.75};
    double dbl2[]={-4.9, 2.3, -5};
    mxArray *A, *B;

    A=mxCreateDoubleMatrix(1, 5, mxREAL);
    B=mxCreateDoubleMatrix(1, 3, mxREAL);

    //copy an array to matrix A and B
    memcpy(mxGetPr(A), dbl1, 5 * sizeof(double));
    memcpy(mxGetPr(B), dbl2, 3 * sizeof(double));

    //opening TestVar.mat for writing new data
    pmat=matOpen(outputFile, "w");
    matPutVariable(pmat, "A", A);
    matPutVariable(pmat, "B", B);

    matClose(pmat);

    mxDestroyArray(A);
    mxDestroyArray(B);
}

void onlineGMR::regression()
{


}

/*
void  GMR::regression(GMM_Model* gmmOut, mat data_in, urowvec in, urowvec out)
{
    // Base regression function. Use this one to be as fast as possible.
    // One need to supply a gmmOut object of appropriate size (nbStates = data_in.n_cols, nbVar = size(out))


    Pxi = zeros(data_in.n_cols,gmm->getNumSTATES());
    //Compute the influence of each GMM component, given input x
    // See Eq. (3.0.5) in doc/TechnicalReport.pdf
    for(i=0; i<gmm->getNumSTATES(); i++){
        Mu = gmm->getMU(i)(in);
        Sigma = gmm->getSIGMA(i)(in,in);
        //Mu_tmp.print("Mu(i) = ");			// DEBUGGING
        //Sigma_tmp.print("Sigma(i) = ");	// DEBUGGING
        Gtmp->setMU(Mu);
        Gtmp->setSIGMA(Sigma);
        Pxi.col(i) = gmm->getPRIORS(i) * (Gtmp->getPDFValue(data_in));
    }
    //Priors.print("Priors = ");	// DEBUGGING
    //data_in->getData().print("t = ");	// DEBUGGING
    //Pxi.print("Pxi = ");	// DEBUGGING
    beta = Pxi / repmat(sum(Pxi,1),1,gmm->getNumSTATES()); // See Eq. (3.0.5) in doc/TechnicalReport.pdf

    //beta.print("beta = ");	// DEBUGGING
    for(t=0; t<data_in.n_cols; t++){
        MuOut.zeros(out.n_elem);
        SigmaOut.zeros(out.n_elem,out.n_elem);
        for(i=0; i<gmm->getNumSTATES(); i++){
            Mu = gmm->getMU(i);
            Sigma = gmm->getSIGMA(i);
            // Pre compute inverse, use inv_sympd to improve performance
            InvSigmaInIn = (Sigma(in,in).i());

            MuOutTmp = Mu(out) + Sigma(out,in) * InvSigmaInIn * (data_in.col(t)-Mu(in)); // See Eq. (3.0.3) in doc/TechnicalReport.pdf
            SigmaOutTmp = Sigma(out,out) - Sigma(out,in) * InvSigmaInIn * Sigma(in,out); // See Eq. (3.0.4) in doc/TechnicalReport.pdf
            MuOut = MuOut + beta(t,i) * MuOutTmp; // See Eq. (3.0.2) in doc/TechnicalReport.pdf
            SigmaOut = SigmaOut + beta(t,i) * SigmaOutTmp; // See Eq. (3.0.2) in doc/TechnicalReport.pdf
        }
//		COMPONENTS.push_back( GaussianDistribution(MuOut, SigmaOut) );
        gmmOut->getCOMPONENTS(t).setMU(MuOut);
        gmmOut->getCOMPONENTS(t).setSIGMA(SigmaOut);

    }

//	GMM_Model* gmmOut;
//	gmmOut->setCOMPONENTS(COMPONENTS);
//	return gmmOut;

}

void GMR::setGMMModel(GMM_Model* gmmmodel)
{
    gmm = gmmmodel;

    // Initial settings for regression
    Gtmp= new GaussianDistribution(gmm->getNumSTATES());
}

} //end of pbdlib namespace

*/



onlineGMR::~onlineGMR()
{

}
