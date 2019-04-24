int cur_line = 0;
while(fgets(line, 512, in) != NULL) {
     if (cur_line == 2) { // 3rd line
     /* get a line, up to 512 chars from in.  done if NULL */
     sscanf (line, "%s %s %s \n",string1,string2,string3);
     // now you should store or manipulate those strings

     break;
     }
     cur_line++;
}
