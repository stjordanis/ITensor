#include "itensor/all.h"

using namespace itensor;

ITensor
makeId(Index const& s)
    {
    auto Id = ITensor(s,prime(s));
    Id.set(s=1,prime(s)=1,1);
    Id.set(s=2,prime(s)=2,1);
    return Id;
    }

ITensor
makeSp(Index const& s)
    {
    auto Sp = ITensor(s,prime(s));
    Sp.set(s=2,prime(s)=1, 1);
    return Sp;
    }

ITensor
makeSm(Index const& s)
    {
    auto Sm = ITensor(s,prime(s));
    Sm.set(s=1,prime(s)=2,1);
    return Sm;
    }

ITensor
makeSz(Index const& s)
    {
    auto Sz = ITensor(s,prime(s));
    Sz.set(s=1,prime(s)=1, 0.5);
    Sz.set(s=2,prime(s)=2,-0.5);
    return Sz;
    }


int main()
    {
    Real beta = 1.;

    //
    // Random initial wavefunction
    //
    auto s1 = Index(2,"s1");
    auto s2 = Index(2,"s2");
    auto psi_init = randomITensor(s1,s2);
    psi_init /= norm(psi_init);

    //PrintData(psi);

    //
    // Single-site operators
    //
    auto Sz1 = makeSz(s1);
    auto Sz2 = makeSz(s2);
    auto Sp1 = makeSp(s1);
    auto Sp2 = makeSp(s2);
    auto Sm1 = makeSm(s1);
    auto Sm2 = makeSm(s2);
    auto Id1 = makeId(s1);
    auto Id2 = makeId(s2);

    //
    // Two-site Heisenberg Hamiltonian
    //
    auto H = Sz1*Sz2 + 0.5*Sp1*Sm2 + 0.5*Sm1*Sp2;

    // Initial energy expectation value
    auto initEn = elt(dag(prime(psi_init)) * H * psi_init);
    printfln("\nInitial energy = %.10f",initEn);


    //
    // Make exp(-beta*H)
    //
    auto expH = expHermitian(H,-beta);

    auto psi = expH*psi_init;
    psi.noPrime();
    psi /= norm(psi);

    auto En = elt(dag(prime(psi)) * H * psi);
    printfln("At beta=%.1f, energy = %.10f",beta,En);

    //
    // TODO
    // (1) Compute the SVD of psi,
    //     and look at the singular values
    //

    //
    // TODO
    // (2) Use the spectrum of the density matrix
    //     (squares of singular values)
    //     to compute entanglement entropy
    //    


    return 0;
    }
