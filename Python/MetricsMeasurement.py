
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
        self.startTime=time.clock()
    
    def start(self,descriptionStr):
        self.m_descriptionStr=descriptionStr
        self.startTime=time.clock()

    def stop(self):
        self.stopTime=time.clock()
        print("CPU TIME[%s] - %d seconds" %(self.m_descriptionStr,self.stopTime-self.startTime))
