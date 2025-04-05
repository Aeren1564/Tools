import os
import shutil
import tarfile
import gzip
import zipfile
import subprocess
import sys
import bz2
import lzma

def decompress_file(file_path):
	file_path = os.path.abspath(file_path)
	output_dir = os.path.dirname(file_path)
	filename = os.path.basename(file_path)
	lower_name = filename.lower()

	try:
		if lower_name.endswith('.7z'):
			subprocess.run(['7z', 'x', file_path, '-o' + output_dir], check=True)
		elif lower_name.endswith(('.tar.gz', '.tgz', '.tar.bz2', '.tar.xz', '.tar.zst')):
			with tarfile.open(file_path) as tar:
				tar.extractall(path=output_dir)
		elif lower_name.endswith('.zip'):
			with zipfile.ZipFile(file_path, 'r') as zip_ref:
				zip_ref.extractall(output_dir)
		elif lower_name.endswith('.rar'):
			subprocess.run(['unrar', 'x', file_path, output_dir], check=True)
		elif lower_name.endswith('.gz'):
			outfile = os.path.join(output_dir, os.path.splitext(filename)[0])
			with gzip.open(file_path, 'rb') as f_in, open(outfile, 'wb') as f_out:
				shutil.copyfileobj(f_in, f_out)
		elif lower_name.endswith('.bz2'):
			outfile = os.path.join(output_dir, os.path.splitext(filename)[0])
			with bz2.open(file_path, 'rb') as f_in, open(outfile, 'wb') as f_out:
				shutil.copyfileobj(f_in, f_out)
		elif lower_name.endswith('.xz'):
			outfile = os.path.join(output_dir, os.path.splitext(filename)[0])
			with lzma.open(file_path, 'rb') as f_in, open(outfile, 'wb') as f_out:
				shutil.copyfileobj(f_in, f_out)
		elif lower_name.endswith('.lzma'):
			outfile = os.path.join(output_dir, os.path.splitext(filename)[0])
			with lzma.open(file_path, 'rb') as f_in, open(outfile, 'wb') as f_out:
				shutil.copyfileobj(f_in, f_out)
		elif lower_name.endswith('.zst') or lower_name.endswith('.tar.zst'):
			subprocess.run(['unzstd', file_path], check=True)
		elif lower_name.endswith('.Z'):
			subprocess.run(['uncompress', file_path], check=True)
		else:
			print(f"Unsupported file format: {file_path}")
			return False

		print(f"Decompressed: {file_path} to {output_dir}")
		os.remove(file_path)
		return True
	except Exception as e:
		print(f"Error decompressing {file_path}: {e}")
		return False

def decompress_files(file_list):
	for file in file_list:
		decompress_file(file)

if __name__ == '__main__':
	if len(sys.argv) < 2:
		print("Usage: python decompress.py <file1> <file2> ...")
		sys.exit(1)
	file_list = [os.path.abspath(file) for file in sys.argv[1:]]
	decompress_files(file_list)