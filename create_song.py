__author__ = 'scobb_000'

def determine_newline(num):
    if num % 4 == 0:
        return '\n'
    else:
        return ''

def main():
    bass_list = 'D3,D3,r,D3,r,D3,D3,r,r,r,r,r,G3,r,r,r,r,' + \
        'G3,r,r,E3,r,r,C2,r,r,F3,r,G3,r,Gflat3,F3,r,' + \
        'tE3,tC4,tE4,F4,r,D4,E4,r,C4,r,A3,B3,G3,r,r,' + \
        'G3,r,r,E3,r,r,C2,r,r,F3,r,G3,r,Gflat3,F3,r,' + \
        'tE3,tC4,tE4,F4,r,D4,E4,r,C4,r,A3,B3,G3,r,r,' + \
        'r,r,E5,Eflat5,D5,B4,r,C5,r,E4,F4,G4,r,C4,E4,F4,' + \
        'r,r,E5,Eflat5,D5,B4,r,C5,r,F5,r,F5,F5,r,r,r,' + \
        'r,r,E5,Eflat5,D5,B4,r,C5,r,E4,F4,G4,r,C4,E4,F4,' + \
        'r,r,Aflat3,r,r,Bflat3,r,r,C4,r,r,r,r,r,r,r,' +\
        'r,r,E5,Eflat5,D5,B4,r,C5,r,E4,F4,G4,r,C4,E4,F4,' + \
        'r,r,E5,Eflat5,D5,B4,r,C5,r,F5,r,F5,F5,r,r,r,' + \
        'r,r,E5,Eflat5,D5,B4,r,C5,r,E4,F4,G4,r,C4,E4,F4,' + \
        'r,r,Aflat3,r,r,Bflat3,r,r,C4,r,r,r,r,r,r,r,' +\
        'Aflat2,Aflat4,r,Eflat3,r,Aflat4,Aflat3,r,G3,E4,r,C3,C4,r,r,r,' +\
        'Aflat2,Aflat4,r,Eflat3,r,Aflat4,Aflat3,r,r,r,r,r,r,r,r,r,' +\
        'Aflat2,Aflat4,r,Eflat3,r,Aflat4,Aflat3,r,G3,E4,r,C3,C4,r,r,r,' +\
        'D3,D3,r,D3,r,D3,D3,r,r,r,r,r,G3,r,r,r,r,G3'


    tag_mel = 'Aflat3,D5,r,D5,D5,r,A3,Eflat5,r,Eflat5,Eflat5,r,Bflat3,E5,r,E5,E5,r,F5,r,F5'
    tag_bass = 'Aflat4,A4,Bflat4'

    note_list = 'E5,E5,r,E5,r,C5,E5,r,G5,r,r,r,G4,r,r,r,' + \
        'C5,r,r,G4,r,r,E4,r,r,A4,r,B4,r,Bflat4,A4,r,tG4,tE5,tG5,A5,r,F5,G5,r,E5,r,C5,D5,B4,r,r,' +\
        'C5,r,r,G4,r,r,E4,r,r,A4,r,B4,r,Bflat4,A4,r,tG4,tE5,tG5,A5,r,F5,G5,r,E5,r,C5,D5,B4,r,r,' +\
        'C3,r,G5,Gflat5,F5,Eflat5,C4,E5,F3,Aflat4,A4,C5,C4,A4,C5,D5,C3,r,G5,Gflat5,F5,Eflat5,G3,E5,' + \
        'r,C6,r,C6,C6,r,G3,r,C3,r,G5,Gflat5,F5,Eflat5,C4,E5,F3,Aflat4,A4,C5,C4,A4,C5,D5,' +\
        'C3,r,Eflat5,r,r,D5,r,r,C5,r,r,G3,G3,r,C3,r,' +\
        'C5,C5,r,C5,r,C5,D5,r,E5,C5,r,A4,G4,r,G3,r,' +\
        'C5,C5,r,C5,r,C5,D5,E5,G3,r,r,C3,r,r,G2,r,' +\
        'C5,C5,r,C5,r,C5,D5,r,E5,C5,r,A4,G4,r,G3,r,' +\
        'E5,E5,r,E5,r,C5,E5,r,G5,r,r,r,G4,r,r,r,C5'

    parse(note_list, 'music')
    parse(bass_list, 'bass')
    parse_tag_bass(tag_bass)
    parse(tag_mel, 'tag_mel')


def parse_tag_bass(notes):
    num = 0
    ret_val = '{'
    for note in notes.split(','):
        if num % 4 == 0:
            ret_val += '\n'
        num += 1
        sub = determine_newline(num)
        ret_val += '{%s, 12, 0},%s{%s, 60, 100},' % (note, sub, note)
        num += 1

    ret_val += '{B4, 12, 100},{B4,12,0},{B4,85,100}'
    num += 3
    ret_val += '};'
    ret_val = ('#define BASS_TAG_SIZE %d\nNote %s[%d] = ' % (num, 'bass_tag', num)) + ret_val
    print(ret_val)



def parse(notes, name):
    num = 0
    ret_val = '{'
    for note in notes.split(','):
        if num % 4 == 0:
            ret_val += '\n'
        if note == 'r':
            ret_val += '{E5, 12, 0},'
            num += 1
        elif note.startswith('t'):
            note = note.replace('t', '')
            num += 1
            sub = determine_newline(num)
            ret_val += '{%s, 12, 100},%s{%s, 4, 0},' % (note, sub, note)
            num += 1
        else:
            num += 1
            sub = determine_newline(num)
            ret_val += '{%s, 8, 100},%s{%s, 4, 0},' % (note, sub, note)
            num += 1

    ret_val += '};'
    ret_val = ('#define SIZE %d\nNote %s[%d] = ' % (num, name, num)) + ret_val
    print(ret_val)


if __name__ == '__main__':
    main()