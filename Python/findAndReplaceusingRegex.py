import re

# Eg: (a,100,200),(b,22,22) will be converted as myText.append(["a",100,200])

with open ('input.txt', 'r' ) as f:
    content = f.read()
    # Split each input as new line
    content_new = re.sub('\),', r')\n', content, flags = re.M)

    # put second double quotes for period tag
    content_new = re.sub('(\(.*?),(.*)', r'\1",\2', content_new, flags = re.M)

    # put first double quotes for period tag
    content_new = re.sub('\(', r'("', content_new, flags = re.M)

    # append myText.append
    content_new = re.sub('\(', r'myText.append([', content_new, flags = re.M)

    #At end, close the bracket ])
    content_new = re.sub('\)', r'])', content_new, flags = re.M)

    print(content_new)
