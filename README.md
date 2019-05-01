# MTDCode
To run over the data file ,do:
cmsRun runHits_cfg.py eosdirs=filepath pattern='.root' output='./filename.root' crysLayout=barzflat useMTDTrack=True dumpRecHits=True runMTDReco=True

To get plots:
python drawHists.py --inputDir=filepath --pattern='pattern.root' --output=output.root
