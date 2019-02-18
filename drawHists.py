import ROOT as R
import math as M
import argparse
import subprocess
import numpy as np
import os

def goodTrack(evt, itrack , chi2cut, skipMCmatching):
    #acceptance cuts
    if (evt.track_pt[itrack]<0.7):
        return False
    if (abs(evt.track_eta[itrack])>3.):
        return False
    #for the moment use matching with mc gen particle
    if (abs(evt.track_mcMatch_DR[itrack])>0.05 and not skipMCmatching):
        return False
    if (abs(evt.track_pt[itrack]/evt.track_mcMatch_genPt[itrack]-1.)>0.1 and not skipMCmatching):
        return False
#    if (evt.track_normalizedChi2[itrack] > chi2cut):
#        return False
#    if (evt.track_eta_atBTL[itrack]<-100 and evt.track_eta_atETL[itrack]<-100):
#        return False
    return True

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

if (args.inputDir != "" and args.inputDir !=None):
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
    f=R.TFile.Open(args.input)
    dh=f.Get("DumpHits")

histos = {}

# time offset introduced in mtd2 due to light collection time (pitch.z()/2 * 7.5ps for bars)
t_offset={}
t_offset['ETL']=-0.0066
t_offset['BTL']=0.
if args.layout == "barzflat":
    t_offset['BTL']=0.226875-0.0115
elif args.layout == "barphi":
    t_offset['BTL']=0.160
elif args.layout == "tile":
    t_offset['BTL']=0.200

histos["track_pt"]=R.TH1F("track_pt","track_pt",100,0.,10.)
histos["track_eta"]=R.TH1F("track_eta","track_eta",100,0.,3,)
histos["track_eta_lowPt"]=R.TH1F("track_eta_lowPt","track_eta_lowPt",100,0.,3,)
histos["track_phi"]=R.TH1F("track_phi","track_phi",1000,-M.pi,M.pi)
#histos["track_eta_1"]=R.TH1F("track_eta_1","track_eta_1",100,0.,3,)
histos["track_eta_sel"]=R.TH1F("track_eta_sel","track_eta_sel",100,0.,3,)
histos["track_phi_sel"]=R.TH1F("track_phi_sel","track_phi_sel",1000,-M.pi,M.pi)
histos["eff_eta"]=R.TH1F("eff_eta","eff_eta",100,0.,3,)
histos["eff_phi"]=R.TH1F("eff_phi","eff_phi",1000,-M.pi,M.pi)
histos["recHits_eta_ETL"]=R.TH1F("recHits_eta_ETL","recHits_eta_ETL",100,0.,3,)
histos["recHits_phi_ETL"]=R.TH1F("recHits_phi_ETL","recHits_phi_ETL",1000,-M.pi,M.pi)
histos["recHits_eta_ETL_sel"]=R.TH1F("recHits_eta_ETL_sel","recHits_eta_ETL_sel",100,0.,3,)
histos["recHits_phi_ETL_sel"]=R.TH1F("recHits_phi_ETL_sel","recHits_phi_ETL_sel",1000,-M.pi,M.pi)
histos["occupancy_eta_ETL"]=R.TH1F("occupancy_eta_ETL","occupancy_eta_ETL",100,0.,3,)
histos["occupancy_phi_ETL"]=R.TH1F("occupancy_phi_ETL","occupancy_phi_ETL",1000,-M.pi,M.pi)



#create hist to draw energy distribution plot
#histos["h_recHit_energy"]=R.TH1F("h_recHit_energy","h_recHit_energy")
histos["ETLrecHits_eta_h"]=R.TH1F("ETLrecHits_eta_h","ETLrecHits_eta_h",100,1.5,3,)
histos["ETLrecHits_eta_sel"]=R.TH1F("ETLrecHits_eta_sel","ETLrecHits_eta_sel",100,1.5,3,)
histos["BTLrecHits_eta_h"]=R.TH1F("BTLrecHits_eta_h","BTLrecHits_eta_h",200,0.,1.5,)
histos["BTLrecHits_eta_sel"]=R.TH1F("BTLrecHits_eta_sel","BTLrecHits_eta_sel",200,0.,1.5,)

for det in ["BTL","ETL"]:
    histos[det+"track_pt"]= R.TH1F (det+"track_pt" ,det+"track_pt",100,0.,10.)
    histos[det+"track_eta"]=R.TH1F(det+"track_eta",det+"track_eta",100,0.,3,)
    histos[det+"track_eta_1"]=R.TH1F(det+"track_eta_1",det+"track_eta_1",100,0.,3,)
    histos[det+"track_eta_lowPt"]=R.TH1F(det+"track_eta_lowPt",det+"track_eta_lowPt",100,0.,3,)
    histos[det+"track_phi"]=R.TH1F(det+"track_phi",det+"track_phi",2000,0.,M.pi)
    histos[det+"track_phi_1"]=R.TH1F(det+"track_phi_1",det+"track_phi_1",2000,0.,M.pi)
    histos[det+"track_eta_sel"]=R.TH1F(det+"track_eta_sel",det+"track_eta_sel",100,0.,3,)
    histos[det+"track_phi_sel"]=R.TH1F(det+"track_phi_sel",det+"track_phi_sel",2000,0.,M.pi)
    
    #histos[det+"eff_eta"]=R.TH1F(det+"eff_eta",det+"eff_eta",100,0.,3,)
    #histos[det+"eff_phi"]=R.TH1F(det+"eff_phi",det+"eff_phi",2000,-M.pi,M.pi)
    
    

    histos[det+"recHit_energy"]=R.TH1F(det+"recHit_energy",det+"recHit_energy",100,0.,20.)
    histos[det+"recHit_time"]=R.TH1F(det+"recHit_time",det+"recHit_time",100,0.,25.)
    histos[det+"recHit_energy_h"]=R.TH1F(det+"recHit_energy_h",det+"recHit_energy_h",100,0.,1.5)

  
histos["h_ETL_ring"]=R.TH1F("h_ETL_ring","h_ETL_ring",50,0,50)
histos["h_ETL_recHits_energy"]=R.TH1F("h_ETL_recHits_energy","h_ETL_recHits_energy",1000,0.,10)
for iRing in range(1,12):
    histos["h_ETL_recHits_energy"+str(iRing)]=R.TH1F("h_ETL_recHits_energy"+str(iRing),"h_ETL_recHits_energy"+str(iRing),1000,0.,10)
    histos["ETL_occupancy_vs_threshold"+str(iRing)]=R.TH2F("ETL_occupancy_vs_threshold"+str(iRing),"ETL_occupancy_vs_threshold"+str(iRing),1000,0.,10,1100,0.,1.1)
    histos["ETL_recHits_eta"+str(iRing)]=R.TH1F("ETL_recHits_eta"+str(iRing),"ETL_recHits_eta"+str(iRing),1000,1.5,3,)
histos["ETL_occupancy_vs_threshold"]=R.TH2F("ETL_occupancy_vs_threshold","ETL_occupancy_vs_threshold",1000,0.,10,1100,0.,1.1)
Total_mod=[64.,64.,80.,96.,112.,112.,128.,144.,160.,160.,176.]
Num_Events=0

det_id = { 'BTL':1  , 'ETL':2 }
etaCut = { 'BTL':[0,1.5]  , 'ETL':[1.5,3] }

if (args.dumpAll):
    print "Dumping also non matched MTD hits"

if (args.dumpHits):
    print "Dumping RecHits"

for ievent,event in enumerate(dh):
    if (int(args.events) != -1 and ievent>int(args.events)):
        break
    if (ievent%1==0):
        print "Analysing event %d"%ievent
    
    if (args.dumpAll):    
        for det in ["BTL","ETL"]:
            for iclus in range(0,event.clusters_n):
                if ( event.clusters_det[iclus] !=  det_id[det] ):
                    continue 
                histos[det+"cluster_energy"].Fill(event.clusters_energy[iclus])
                histos[det+"cluster_time"].Fill(event.clusters_time[iclus])
                histos[det+"cluster_size"].Fill(event.clusters_size[iclus])
                histos[det+"cluster_sizeX"].Fill(event.clusters_size_x[iclus])
                histos[det+"cluster_sizeY"].Fill(event.clusters_size_y[iclus])
                histos[det+"cluster_seedEnergyRatio"].Fill(event.clusters_seed_energy[iclus]/event.clusters_energy[iclus])

            if (args.dumpHits):    
                for ihit in range(0,event.recHits_n):
                    if ( event.recHits_det[ihit] !=  det_id[det] ):
                        continue 
                    histos[det+"recHit_energy"].Fill(event.recHits_energy[ihit])
                    histos[det+"recHit_time"].Fill(event.recHits_time[ihit])

    #dr_cut = 0.05
    #recHit_threshold=0.01
    
    for iRecHit in range(0,event.recHits_n):
        if(event.recHits_det[iRecHit]==2):  #only keep recHits in ETL
            histos["ETLrecHits_eta_h"].Fill(event.recHits_eta[iRecHit])
            histos["h_ETL_recHits_energy"].Fill(event.recHits_energy[iRecHit])
	        #histos["recHits_eta_ETL"].Fill(event.recHits_eta[iRecHit])
            #histos["recHits_phi_ETL"].Fill(event.recHits_eta[iRecHit])
            histos["h_ETL_ring"].Fill(event.recHits_rr[iRecHit])
            for iRing in range (1,12):
                if (event.recHits_rr[iRecHit]==iRing):
                    histos["h_ETL_recHits_energy"+str(iRing)].Fill(event.recHits_energy[iRecHit])
                    histos["ETL_recHits_eta"+str(iRing)].Fill(event.recHits_eta[iRecHit])                
       
        
        
        
        #if(event.recHits_energy[iRecHit]>recHit_threshold):
        #    histos["recHits_eta_ETL_sel"].Fill(event.recHits_eta[iRecHit])
        #    histos["recHits_phi_ETL_sel"].Fill(event.recHits_eta[iRecHit])
    Num_Events+=1


    for itrack in range(0,len(event.track_idx)):
        recHit_energy_totalval_BTL = 0   #the total value of recHit energy from BTL
        recHit_energy_totalval_ETL = 0   #from ETL
        n_recHits_BTL = 0
        n_recHits_ETL = 0

        isNuGun = True if args.input.find("NuGun")>0 else False
        if (not goodTrack(event,itrack,args.chi2cut,isNuGun)):
            continue
        if (event.track_eta_atBTL[itrack]>-100.):  #if the track is from BTL
            for irecHit in range(0,event.recHits_n):   #loop over all recHits
                dR = M.sqrt(pow((event.track_eta_atBTL[itrack]-event.recHits_eta[irecHit]),2)+pow(event.track_phi_atBTL[itrack]-event.recHits_phi[irecHit],2))
                #print "dR = %f"%dR
                if (event.recHits_det[irecHit]==1 and dR<0.05):
                    recHit_energy_totalval_BTL+=event.recHits_energy[irecHit]
                    n_recHits_BTL+=1                   
                    #print "For BTL and %d th track, energy: %f" % (itrack,event.recHits_energy[irecHit])
            
            histos["BTLrecHit_energy_h"].Fill(recHit_energy_totalval_BTL)
            histos["BTLtrack_eta_1"].Fill(abs(event.track_eta_atBTL[itrack]))
            histos["BTLtrack_phi_1"].Fill(event.track_phi_atBTL[itrack])
            if(recHit_energy_totalval_BTL>0):
                histos["BTLtrack_eta_sel"].Fill(abs(event.track_eta_atBTL[itrack]))
                histos["BTLtrack_phi_sel"].Fill(event.track_phi_atBTL[itrack])
            
        elif(event.track_eta_atETL[itrack]>-100. and abs(event.track_eta[itrack])>1.5 and abs(event.track_eta[itrack])<3.0):
            for irecHit in range(0,event.recHits_n):   #loop over all recHits
                if (event.recHits_det[irecHit]==2 and M.sqrt(pow((event.track_eta_atETL[itrack]-event.recHits_eta[irecHit]),2)+pow(event.track_phi_atETL[itrack]-event.recHits_phi[irecHit],2))<0.05):
                    recHit_energy_totalval_ETL+=event.recHits_energy[irecHit]
                    n_recHits_ETL+=1
                    #print "For ETL and %d th track, energy: %f" % (itrack,event.recHits_energy[irecHit])
            histos["ETLrecHit_energy_h"].Fill(recHit_energy_totalval_ETL)
            histos["ETLtrack_eta_1"].Fill(abs(event.track_eta_atETL[itrack]))
            histos["ETLtrack_phi_1"].Fill(event.track_phi_atETL[itrack])
            if(recHit_energy_totalval_ETL>0.015):
                histos["ETLtrack_eta_sel"].Fill(abs(event.track_eta_atETL[itrack]))
                histos["ETLtrack_phi_sel"].Fill(event.track_phi_atETL[itrack])
            
        histos["track_pt"].Fill(event.track_pt[itrack])
        histos["track_eta"].Fill(abs(event.track_eta[itrack]))
        if ((n_recHits_BTL+n_recHits_ETL)>0):
            histos["track_eta_sel"].Fill(abs(event.track_eta[itrack]))
            histos["track_phi_sel"].Fill(event.track_phi[itrack])
        if (event.track_pt[itrack]<1.):
            histos["track_eta_lowPt"].Fill(abs(event.track_eta[itrack]))
        histos["track_phi"].Fill(event.track_phi[itrack])
        
        
        for det in ["BTL","ETL"]:
            if ( 
                abs(event.track_eta[itrack]) < etaCut[det][0] or
                abs(event.track_eta[itrack]) > etaCut[det][1]
                ):
                continue
            
            histos[det+"track_pt"].Fill(event.track_pt[itrack])
            histos[det+"track_eta"].Fill(abs(event.track_eta[itrack]))
            if (event.track_pt[itrack]<1.):
                histos[det+"track_eta_lowPt"].Fill(abs(event.track_eta[itrack]))
            histos[det+"track_phi"].Fill(event.track_phi[itrack])

            

            
    
for iThreshold in np.arange(0,10,0.01):
    occupancy=(1.0*histos["h_ETL_recHits_energy"].Integral(histos["h_ETL_recHits_energy"].FindBin(iThreshold),histos["h_ETL_recHits_energy"].FindBin(10)))/(Num_Events*2592.0)   #2592 is total number of modules in ETL
    histos["ETL_occupancy_vs_threshold"].Fill(iThreshold,occupancy)
    for iRing in range(1,12):
        occupancy_ring=(1.0*histos["h_ETL_recHits_energy"+str(iRing)].Integral(histos["h_ETL_recHits_energy"+str(iRing)].FindBin(iThreshold),histos["h_ETL_recHits_energy"+str(iRing)].FindBin(10)))/(Num_Events*2.0*Total_mod[iRing-1])
        histos["ETL_occupancy_vs_threshold"+str(iRing)].Fill(iThreshold,occupancy_ring)
        histos["ETL_recHits_eta"+str(iRing)].Scale(1.0/(Num_Events*2.0*Total_mod[iRing-1]))



histos["BTLeff_eta"]=R.TGraphAsymmErrors(histos["BTLtrack_eta_sel"],histos["BTLtrack_eta_1"])
histos["BTLeff_phi"]=R.TGraphAsymmErrors(histos["BTLtrack_phi_sel"],histos["BTLtrack_phi_1"])
histos["ETLeff_eta"]=R.TGraphAsymmErrors(histos["ETLtrack_eta_sel"],histos["ETLtrack_eta_1"])
histos["ETLeff_phi"]=R.TGraphAsymmErrors(histos["ETLtrack_phi_sel"],histos["ETLtrack_phi_1"])

#histos["ETLefficiency_eta"]=R.TGraphAsymmErrors(histos["ETLrecHits_eta_sel"],histos["ETLrecHits_eta_h"])
#histos["BTLefficiency_eta"]=R.TGraphAsymmErrors(histos["BTLrecHits_eta_sel"],histos["BTLrecHits_eta_h"])



#Check to see if output directory exists. if not, create it
outputDir = args.output.split('/')[0]
if (not os.path.exists("./"+outputDir)):
    os.system("mkdir "+outputDir)

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
