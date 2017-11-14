enum SelectionBit {
 kLoose    =(1<<0),
 kFake     =(1<<1),
 kMedium   =(1<<2),
 kTight    =(1<<3),
 kDxyz     =(1<<4),
 kTrigger  =(1<<5)
};

enum TriggerBits {
    kMETTrig	   =(1<<0),
    kSinglePhoTrig =(1<<1),
    kMuEGTrig	   =(1<<2),
    kMuMuTrig	   =(1<<3),
    kMuTrig	   =(1<<4),
    kEGEGTrig	   =(1<<5),
    kEGTrig	   =(1<<6),
    kMuTagTrig     =(1<<7),
    kEGTagTrig     =(1<<8)
};

const double mass_el = 0.000510998928;
const double mass_mu = 0.10566;
