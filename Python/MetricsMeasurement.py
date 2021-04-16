import time
import os, psutil


class ElapsedTime:
    m_descriptionStr="ElasedTime"
    startTime=0
    stopTime=0

    def start(self):
        self.startTime=time.time()*1000
    
    def start(self,descriptionStr):
        self.m_descriptionStr=descriptionStr
        self.startTime=time.time()*1000

    def stop(self):
        self.stopTime=time.time()*1000
        print("%s - %d milli seconds" %(self.m_descriptionStr,self.stopTime-self.startTime) )


class CpuTime:
    m_descriptionStr="ElasedTime"
    startTime=0
    stopTime=0

    def start(self):
        self.startTime=time.clock()*1000
    
    def start(self,descriptionStr):
        self.m_descriptionStr=descriptionStr
        self.startTime=time.clock()*1000

    def stop(self):
        self.stopTime=time.clock()*1000
        print("CPU TIME[%s] - %d milli seconds" %(self.m_descriptionStr,self.stopTime-self.startTime))

       
class MemoryUsage:

    m_descriptionStr="MemoryUsage"
    startTime=0
    stopTime=0

    def peakMemoryUsage(self):
        process = psutil.Process(os.getpid())
        memoryInBytes=process.memory_info().rss
        print("PeakMemoryUsage(KB) %d"%(memoryInBytes/1024))
