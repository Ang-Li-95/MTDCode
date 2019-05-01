import ROOT as R
import math as M
import argparse
import subprocess
import numpy as np
import os

def goodTrack(evt, itrack , chi2cut, skipMCmatching):
    #acceptance cuts
    if (evt.track_pt[itrack]<3.0):
        return False
    if (abs(evt.track_eta[itrack])>3.):
        return False
    #for the moment use matching with mc gen particle
    if (abs(evt.track_mcMatch_DR[itrack])>0.05 and not skipMCmatching):
        return False
    if (abs(evt.track_pt[itrack]/evt.track_mcMatch_genPt[itrack]-1.)>0.1 and not skipMCmatching):
        return False
    '''
    if (evt.track_pt[itrack]<9.8):
	return False
    if (evt.track_pt[itrack]>10.2):
        return False
    if (abs(evt.track_eta_atBTL[itrack])<0.8):
        return False
    if (abs(evt.track_eta_atBTL[itrack])>1.0):
        return False
    '''
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
parser.add_argument('--firstEvent',dest='firstEvent', default='0')
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







histos["BTLrecHits_length1_minus_length2"]=R.TH1F("BTLrecHits_length1_minus_length2","BTLrecHits_length1_minus_length2",50,-0.5,0.5)
histos["BTLrecHits_total_length"]=R.TH1F("BTLrecHits_total_length","BTLrecHits_total_length",75,-0.5,1)
histos["BTLrecHits_length_1"]=R.TH1F("BTLrecHits_length_1","BTLrecHits_length_1",50,-0.5,0.5)
histos["BTLrecHits_length_2"]=R.TH1F("BTLrecHits_length_2","BTLrecHits_length_2",50,-0.5,0.5)  
histos["BTLrecHits_t1_travel_vs_t2_travel"]=R.TH2F("BTLrecHits_t1_travel_vs_t2_travel","BTLrecHits_t1_travel_vs_t2_travel",50,-2.,3.,50,-2.,3.)
histos["BTLrecHits_x1_vs_x2"]=R.TH2F("BTLrecHits_x1_vs_x2","BTLrecHits_x1_vs_x2",50,-0.5,0.5,50,-0.5,0.5)
histos["BTLrecHits_average_time"]=R.TH2F("BTLrecHits_average_time","BTLrecHits_average_time",300,0,60,300,0,60)
histos["BTLrecHits_t_travel_track_t0"]=R.TH2F("BTLrecHits_t_travel_track_t0","BTLrecHits_t_travel_track_t0",50,0,10,50,0,10)


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

    
    speed_of_light = 0.16472113 #in units of 1e+09		unit of time is ps(1e-12s)
    c = 0.299792458			#in units of 1e+09
    radius_of_BTL = 1.148


    for nRecHit in range(0,len(event.recHits_eta_uncalibrated)):
        recHitMatched = False
	    if(event.recHits_matched_with_uncalibrated[nRecHit]==0):
		    continue
        for iTrack in range(0,len(event.track_idx)):
                isNuGun_uncal_ = True if args.inputDir.find("NuGun")>0 else False
                if(not goodTrack(event,iTrack,args.chi2cut,isNuGun_uncal_)):
                        continue
                if(not event.track_eta_atBTL[iTrack]>-100.):
                        continue
                deltaR = M.sqrt(pow((event.track_eta_atBTL[iTrack]-event.recHits_eta[nRecHit]),2)+pow(event.track_phi_atBTL[iTrack]-event.recHits_phi[nRecHit],2))
                if(deltaR<0.05):
                        recHitMatched = True
                        break
        if(not (recHitMatched == True)):
                continue
	    histos["BTLrecHits_average_time"].Fill(event.recHits_time[nRecHit],(event.recHits_time1_uncalibrated[nRecHit]+event.recHits_time2_uncalibrated[nRecHit])/2)





    for iuncalRecHit in range(0,len(event.recHits_uncal_time1)):
	recHitMatched = False
	#calculate the time it takes for the track to reach BTL
        #assuming the speed is c and no curved track because of high energy
        angle = M.pi/2.0-2.0*M.atan(M.exp(-event.recHits_uncal_eta[iuncalRecHit]))
        distance_travelled = 100.0*radius_of_BTL/M.cos(angle)
        #t_travel = distance_travelled/c

	for iTrack in range(0,len(event.track_idx)):
		isNuGun_uncal = True if args.inputDir.find("NuGun")>0 else False
		if(not goodTrack(event,iTrack,args.chi2cut,isNuGun_uncal)):
			continue
		if(not event.track_eta_atBTL[iTrack]>-100.):
			continue
		if(event.track_velocity[iTrack]==0):
			continue
		deltaR = M.sqrt(pow((event.track_eta_atBTL[iTrack]-event.recHits_uncal_eta[iuncalRecHit]),2)+pow(event.track_phi_atBTL[iTrack]-event.recHits_uncal_phi[iuncalRecHit],2))   
		if(deltaR<0.01):
			distance_ref_to_recHit = M.sqrt((event.recHits_uncal_x[iuncalRecHit]-event.track_x[iTrack])*(event.recHits_uncal_x[iuncalRecHit]-event.track_x[iTrack])+(event.recHits_uncal_y[iuncalRecHit]-event.track_y[iTrack])*(event.recHits_uncal_y[iuncalRecHit]-event.track_y[iTrack])+(event.recHits_uncal_z[iuncalRecHit]-event.track_z[iTrack])*(event.recHits_uncal_z[iuncalRecHit]-event.track_z[iTrack]))
			t_travelled = distance_ref_to_recHit*0.01/(event.track_velocity[iTrack]*c)-event.track_t[iTrack]
			print "Before: %f cm" %distance_travelled
			print "After: %f cm" %distance_ref_to_recHit
			#histos["BTLrecHits_t_travel_track_t0"].Fill(event.track_t[iTrack],t_travel)
			histos["BTLrecHits_length_1"].Fill(speed_of_light*(event.recHits_uncal_time1[iuncalRecHit]-t_travelled))
        		histos["BTLrecHits_length_2"].Fill(speed_of_light*(event.recHits_uncal_time2[iuncalRecHit]-t_travelled))
        		histos["BTLrecHits_t1_travel_vs_t2_travel"].Fill(event.recHits_uncal_time2[iuncalRecHit]-t_travelled,event.recHits_uncal_time1[iuncalRecHit]-t_travelled)
        		histos["BTLrecHits_x1_vs_x2"].Fill(speed_of_light*(event.recHits_uncal_time2[iuncalRecHit]-t_travelled),speed_of_light*(event.recHits_uncal_time1[iuncalRecHit]-t_travelled))

			recHitMatched = True
			break
	if(not (recHitMatched == True)):
		continue
	histos["BTLrecHits_length1_minus_length2"].Fill(speed_of_light*(event.recHits_uncal_time1[iuncalRecHit]-event.recHits_uncal_time2[iuncalRecHit]))

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
