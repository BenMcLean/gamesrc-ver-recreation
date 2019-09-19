#!/usr/bin/gawk -f
function reverse(str) {
	revret = "";
	for (i=length(str); i>0; --i) {
		revret = revret substr(str, i, 1);
	}
	return(revret);
}

function replace(prefix, domap) {
	do {
		regex = sprintf("%s_[0-9A-F][0-9A-F]*", prefix);
		ret = match($0, regex);
		if (ret) {
			varname = substr($0, RSTART, RLENGTH);
			if (domap) {
				if ((ret > 10) || (!(varname in a))) {
					a[varname] = sprintf("%s_%s", reverse(prefix), substr($0,1,8));
				}
			}
			gsub(varname, a[varname]);
		}
	}
	while (ret);
}

(NR == FNR) {
	replace("dword", 1);
	replace("word", 1);
	replace("byte", 1);
	replace("unk", 1);
}

(NR != FNR) {
	replace("dword", 0);
	replace("word", 0);
	replace("byte", 0);
	replace("unk", 0);
}

END {
	for (varname in a) {
		print varname, a[varname];
	}
}
