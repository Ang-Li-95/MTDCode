import ROOT as R
import math as M
import argparse
import subprocess
import numpy as np


parser = argparse.ArgumentParser()
parser.add_argument('--input',dest='input')
parser.add_argument('--inputDir',dest='inputDir')
parser.add_argument('--pattern',dest='pattern')
parser.add_argument('--output',dest='output')
parser.add_argument('--layout',dest='layout')
parser.add_argument('--chi2cut',dest='chi2cut')
parser.add_argument('--events',dest='events',default='-1')
parser.add_argument('--dumpHits',dest='dumpHits',action='store_true',default=False)
parser.add_argument('--dumpAll',dest='dumpAll',action='store_true',default=False)

args = parser.parse_args()

if (args.inputDir != ""):
    print args.inputDir
    dh=R.TChain("DumpHits")
    files = []
    if args.inputDir[-1] != '/':
        args.inputDir += '/'
    print('>> Creating list of files from: \n'+args.inputDir)
    command = '/bin/find '+args.inputDir+' -type f | grep root | grep -v failed | grep '+args.pattern
    str_files = subprocess.check_output(command,shell=True).splitlines()
    #print str_files
    files.extend(['file:'+ifile for ifile in str_files])
    for file in files:
        print ">> Adding "+file
        dh.Add(file)
else:
    print('>> Opening: '+args.input)
    f=R.TFile(args.input)
    dh=f.Get("DumpHits")

histos = {}



histos["h_ETL_ring"]=R.TH1F("h_ETL_ring","h_ETL_ring",50,0,50)
histos["h_ETL_recHits_energy"]=R.TH1F("h_ETL_recHits_energy","h_ETL_recHits_energy",1000,0.,10)
for iRing in range(1,12):
    histos["h_ETL_recHits_energy"+str(iRing)]=R.TH1F("h_ETL_recHits_energy"+str(iRing),"h_ETL_recHits_energy"+str(iRing),1000,0.,10)
    histos["ETL_occupancy_vs_threshold_numerator"+str(iRing)]=R.TH1F("ETL_occupancy_vs_threshold_numerator"+str(iRing),"ETL_occupancy_vs_threshold_numerator"+str(iRing),1000,0.,10)
    histos["ETL_occupancy_vs_threshold_denominator"+str(iRing)]=R.TH1F("ETL_occupancy_vs_threshold_denominator"+str(iRing),"ETL_occupancy_vs_threshold_denominator"+str(iRing),1000,0.,10)    
    histos["ETL_recHits_eta"+str(iRing)]=R.TH1F("ETL_recHits_eta"+str(iRing),"ETL_recHits_eta"+str(iRing),200,1.5,3,)
histos["ETL_occupancy_vs_threshold_numerator"]=R.TH1F("ETL_occupancy_vs_threshold_numerator","ETL_occupancy_vs_threshold_numerator",1000,0.,10)
histos["ETL_occupancy_vs_threshold_denominator"]=R.TH1F("ETL_occupancy_vs_threshold_denominator","ETL_occupancy_vs_threshold_denominator",1000,0.,10)

Total_mod=[64.,64.,80.,96.,112.,112.,128.,144.,160.,160.,176.]
Num_Events=0



for ievent,event in enumerate(dh):
    if (int(args.events) != -1 and ievent>int(args.events)):
        break
    if (ievent%1==0):
        print "Analysing event %d"%ievent
    
    
    for iRecHit in range(0,event.recHits_n):
        if(not event.recHits_det[iRecHit]==2):  #only keep recHits in ETL
            continue
        histos["h_ETL_recHits_energy"].Fill(event.recHits_energy[iRecHit])
        histos["h_ETL_ring"].Fill(event.recHits_rr[iRecHit])
        for iRing in range (1,12):
            if (event.recHits_rr[iRecHit]==iRing):
                histos["h_ETL_recHits_energy"+str(iRing)].Fill(event.recHits_energy[iRecHit])
                histos["ETL_recHits_eta"+str(iRing)].Fill(event.recHits_eta[iRecHit])
                
	    #if(event.recHits_energy[iRecHit]>recHit_threshold):
        #    histos["recHits_eta_ETL_sel"].Fill(event.recHits_eta[iRecHit])
        #    histos["recHits_phi_ETL_sel"].Fill(event.recHits_eta[iRecHit])
    Num_Events+=1


    
for iThreshold in np.arange(0,10,0.01):
    occupancy_numerator=(1.0*histos["h_ETL_recHits_energy"].Integral(histos["h_ETL_recHits_energy"].FindBin(iThreshold),histos["h_ETL_recHits_energy"].FindBin(10)))
    occupancy_denominator=(Num_Events*2592.0)   #2592 is total number of modules in ETL
    histos["ETL_occupancy_vs_threshold_numerator"].SetBinContent(histos["ETL_occupancy_vs_threshold_numerator"].FindBin(iThreshold),occupancy_numerator)
    histos["ETL_occupancy_vs_threshold_denominator"].SetBinContent(histos["ETL_occupancy_vs_threshold_denominator"].FindBin(iThreshold),occupancy_denominator)
    for iRing in range(1,12):
        occupancy_ring_numerator=(1.0*histos["h_ETL_recHits_energy"+str(iRing)].Integral(histos["h_ETL_recHits_energy"+str(iRing)].FindBin(iThreshold),histos["h_ETL_recHits_energy"+str(iRing)].FindBin(10)))
        occupancy_ring_denominator=(Num_Events*2.0*Total_mod[iRing-1])
        histos["ETL_occupancy_vs_threshold_numerator"+str(iRing)].SetBinContent(histos["ETL_occupancy_vs_threshold_numerator"+str(iRing)].FindBin(iThreshold),occupancy_ring_numerator)
        histos["ETL_occupancy_vs_threshold_denominator"+str(iRing)].SetBinContent(histos["ETL_occupancy_vs_threshold_denominator"+str(iRing)].FindBin(iThreshold),occupancy_ring_denominator)

for iRing in range(1,12):
    histos["ETL_occupancy_vs_threshold"+str(iRing)]= R.TGraphAsymmErrors(histos["ETL_occupancy_vs_threshold_numerator"+str(iRing)],histos["ETL_occupancy_vs_threshold_denominator"+str(iRing)])
    histos["ETL_recHits_eta"+str(iRing)].Scale(1.0/(2.0*Num_Events*Total_mod[iRing-1]))

histos["ETL_occupancy_vs_threshold"]= R.TGraphAsymmErrors(histos["ETL_occupancy_vs_threshold_numerator"],histos["ETL_occupancy_vs_threshold_denominator"])


fOut=R.TFile(args.output,"RECREATE")
for hn, histo in histos.iteritems():
    if isinstance(histo,R.TH1F):
        histo.SetMinimum(0.)
    if isinstance(histo,R.TGraphAsymmErrors):
        histo.SetMinimum(0.)
        histo.SetMaximum(1.1)
    histo.Write()
fOut.Close()
print "Saved histos in "+args.output
